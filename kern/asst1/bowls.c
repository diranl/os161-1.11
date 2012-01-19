/*
 * bowls.c
 *
 * 26-11-2007 : KMS: maintain shared state for cat/mouse problem
 * 21-04-2009 : KMS: added sleep functions
 * 21-04-2009 : KMS: removed debug flag - always print simulation state
 *
 */


/*
 * 
 * Includes
 *
 */
#include <types.h>
#include <lib.h>
#include <synch.h>

/* number of seconds of delay used to simulate eating */
#define CATEATINGTIME 1
#define MOUSEEATINGTIME 3
/* number of seconds of delay used to simulate sleeping */
#define CATSLEEPINGTIME 5
#define MOUSESLEEPINGTIME 3

/*
 *
 * shared simulation state
 * 
 * note: this is state should be used only by the 
 *  functions in this file, hence the static declarations
 *
 */

/* a character array with one entry for each bowl
 *  bowl[i-1] = 'c' if a cat is eating at the ith bowl
 *  bowl[i-1] = 'm' if a mouse is eating at the ith bowl
 *  bowl[i-1] = '-' otherwise */

static char *bowls;

/* the number of bowls */
static int num_bowls;

/* how many cats are currently eating? */
static int eating_cats_count;

/* how many mice are currently eating? */
static int eating_mice_count;

/* semaphore used to provide mutual exclusion
 * for reading and writing the shared simulation state */
static struct semaphore *mutex;


/*
 *
 * functions
 *
 */


/*
 * print_state()
 * 
 * Purpose:
 *   displays the simulation state
 *
 * Arguments:
 *   none
 *
 * Returns:
 *   nothing
 *
 * Notes:
 *   this assumes that it is being called from within
 *   a critical section - it does not provide its own
 *   mutual exclusion
 */
static void
print_state()
{
  int i;

  for(i=0;i<num_bowls;i++) {
    kprintf("%c",bowls[i]);
  }
  kprintf("  Eating Cats: %d  Eating Mice: %d\n",eating_cats_count,
	    eating_mice_count);
  return;
}


/*
 * initialize_bowls()
 * 
 * Purpose:
 *   initializes simulation of cats and mice and bowls
 *
 * Arguments:
 *   unsigned int bowlcount:  the number of food bowls to simulate
 *
 * Returns:
 *   0 on success, 1 otherwise
 */
int
initialize_bowls(unsigned int bowlcount)
{
  unsigned int i;

  if (bowlcount == 0) {
    kprintf("initialize_bowls: invalid bowl count %d\n",bowlcount);
    return 1;
  }

  bowls = kmalloc(bowlcount*sizeof(char));
  if (bowls == NULL) {
    panic("initialize_bowls: unable to allocate space for %d bowls\n",bowlcount);
  }
  /* initialize bowls */
  for(i=0;i<bowlcount;i++) {
    bowls[i] = '-';
  }
  eating_cats_count = eating_mice_count = 0;
  num_bowls = bowlcount;

  /* intialize mutex semaphore */
  mutex = sem_create("bowl mutex",1);
  if (mutex == NULL) {
    panic("initialize_bowls: sem_create failed\n");
  }
  
  return 0;
}

/*
 * cat_eat()
 *
 * Purpose:
 *   simulates a cat eating from a bowl, and checks to
 *   make sure that none of the simulation requirements
 *   have been violated.
 *
 * Arguments:
 *   unsigned int bowlnumber: which bowl the cat should eat from
 *
 * Returns:
 *   nothing
 *
 */

void
cat_eat(unsigned int bowlnumber) {

  /* check the argument */
  if ((bowlnumber == 0) || ((int)bowlnumber > num_bowls)) {
    panic("cat_eat: invalid bowl number %d\n",bowlnumber);
  }

  /* check and update the simulation state to indicate that
   * the cat is now eating at the specified bowl */
  P(mutex);   // start critical section

  /* first check whether allowing this cat to eat will
   * violate any simulation requirements */
  if (bowls[bowlnumber-1] == 'c') {
    /* there is already a cat eating at the specified bowl */
    panic("cat_eat: attempt to make two cats eat from bowl %d!\n",bowlnumber);
  }
  if (eating_mice_count > 0) {
    /* there is already a mouse eating at some bowl */
    panic("cat_eat: attempt to make a cat eat while mice are eating!\n");
  }
  assert(bowls[bowlnumber-1]=='-');
  assert(eating_mice_count == 0);

  /* now update the state to indicate that the cat is eating */
  eating_cats_count += 1;
  bowls[bowlnumber-1] = 'c';

  /* print a summary of the current state */
  kprintf("cat_eat(bowl %d) start: ",bowlnumber);
  print_state();
  kprintf("\n");

  V(mutex);  // end critical section

  /* simulate eating by introducing a delay
   * note that eating is not part of the critical section */
  clocksleep(CATEATINGTIME);

  /* update the simulation state to indicate that
   * the cat is finished eating */
  P(mutex);  // start critical section

  assert(eating_cats_count > 0);
  assert(bowls[bowlnumber-1]=='c');
  eating_cats_count -= 1;
  bowls[bowlnumber-1]='-';

  /* print a summary of the current state */
  kprintf("cat_eat(bowl %d) finish: ",bowlnumber);
  print_state();
  kprintf("\n");
  
  V(mutex);  // end critical section

  return;
}

/*
 * cat_sleep()
 *
 * Purpose:
 *   simulates a cat sleeping
 *
 * Arguments: none
 *
 * Returns: nothing
 *
 */
void
cat_sleep() {
  /* simulate sleeping by introducing a delay */
  clocksleep(CATSLEEPINGTIME);
  return;
}


/*
 * mouse_eat()
 *
 * Purpose:
 *   simulates a mouse eating from a bowl, and checks to
 *   make sure that none of the simulation requirements
 *   have been violated.
 *
 * Arguments:
 *   unsigned int bowlnumber: which bowl the mouse should eat from
 *
 * Returns:
 *   nothing
 *
 */

void
mouse_eat(unsigned int bowlnumber) {

  /* check the argument */
  if ((bowlnumber == 0) || ((int)bowlnumber > num_bowls)) {
    panic("mouse_eat: invalid bowl number %d\n",bowlnumber);
  }

  /* check and updated the simulation state to indicate that
   * the mouse is now eating at the specified bowl. */
  P(mutex);  // start critical section

  /* first check whether allowing this mouse to eat will
   * violate any simulation requirements */
  if (bowls[bowlnumber-1] == 'm') {
    /* there is already a mouse eating at the specified bowl */
    panic("mouse_eat: attempt to make two mice eat from bowl %d!\n",bowlnumber);
  }
  if (eating_cats_count > 0) {
    /* there is already a cat eating at some bowl */
    panic("mouse_eat: attempt to make a mouse eat while cats are eating!\n");
  }
  assert(bowls[bowlnumber-1]=='-');
  assert(eating_cats_count == 0);

  /* now update the state to indicate that the mouse is eating */
  eating_mice_count += 1;
  bowls[bowlnumber-1] = 'm';

  /* print a summary of the current state */
  kprintf("mouse_eat(bowl %d) start: ",bowlnumber);
  print_state();
  kprintf("\n");

  V(mutex);  // end critical section

  /* simulate eating by introducing a delay
   * note that eating is not part of the critical section */
  clocksleep(MOUSEEATINGTIME);

  /* update the simulation state to indicate that
   * the mouse is finished eating */
  P(mutex); // start critical section

  assert(eating_mice_count > 0);
  eating_mice_count -= 1;
  assert(bowls[bowlnumber-1]=='m');
  bowls[bowlnumber-1]='-';

  /* print a summary of the current state */
  kprintf("mouse_eat(bowl %d) finish: ",bowlnumber);
  print_state();
  kprintf("\n");

  V(mutex);  // end critical section
  return;
}

/*
 * mouse_sleep()
 *
 * Purpose:
 *   simulates a mouse sleeping
 *
 * Arguments: none
 *
 * Returns: nothing
 *
 */
void
mouse_sleep() {
  /* simulate sleeping by introducing a delay */
  clocksleep(MOUSESLEEPINGTIME);
  return;
}

