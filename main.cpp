/*
 * AI assignment 5
 * author: codycanning
 * date: Tue Feb 26 17:33:05 2013
 *
 * NOTES: the performance of the algorithm depends on how you populate the Action lists in untried.
 *        e.g. function getActions populates the list as a FIFO queue. This means that the 
 *        algorithm will always go North before any other action (unless the previous action was 
 *        South, in which case it will go West).
 *
 *        Moreover, the algorithm will loop infinitely if it doesn't find the goal state but gets
 *        to the last element in unbacktracked[s']. The algorithm in 4.21 doesn't account for this
 *        either, as it always adds s to the front of unbacktracked[s'] EVEN DURING backtracking.
 *
 */

#include <list>
#include <iostream>
#include <algorithm>

#include "Environment.h"

using namespace std;

#define LENGTH LOCSIZE*LOCSIZE

list<Action> untried[LENGTH];
list<Location> unbacktracked[LENGTH];
Location s;
Action a;

// returns an Action list from the actions in ActStruct ac
list<Action> getActions(ActStruct ac){
  list<Action> actions;
 
  if (ac.N == 1){ actions.push_back(N); }
  if (ac.W == 1){ actions.push_back(W); }
  if (ac.S == 1){ actions.push_back(S); }
  if (ac.E == 1){ actions.push_back(E); }
  return actions;
}

// transforms loc into an array index
int indexify(Location loc){
  return (loc.x * 3) + loc.y;
}

// turns an Action into a string for printing purposes
string report(Action a) {
  string retval;
  switch ( a ) {
  case N: return "N";
  case S: return "S";
  case E: return "E";
  case W: return "W";
  case T: return "T";
  default: return "Invalid action returned!!";
  }
}

// get the action that takes you in the opposite direction of a
Action getOppositeAction( Action a ){
  switch ( a ) {
  case N: return S;
  case S: return N;
  case E: return W;
  default: return E;
  }
}

// online Depth-first-search agent algorithm
Action onlineDFSAgent( Location loc, Environment env)
{
  int i = indexify(loc);

  cout << "s': (" << loc.x << "," << loc.y << ") s: (" << s.x << "," << s.y << ") action: " ;
  if (env.Goal_Test(loc)){
    return T;
  }

  if (binary_search (untried[i].begin(), untried[i].end(), T)) { // new state
    untried[i] = getActions(env.Actions(loc)); 
    untried[i].remove(getOppositeAction(a));
  }
  if (s.x != -1) {
    unbacktracked[i].push_back(s);
  }

  // if all actions have been tried for this state...
  if (untried[i].empty()) {
    // if all previous states have been backtracked...
    if (unbacktracked[i].empty()) {
      return T;
    }
    else { 
      // find the action that backtracks to previous state
      Location unback = unbacktracked[i].front();
      unbacktracked[i].pop_front();
      for (int actInt = N; actInt != T; actInt++) {
        Action act = static_cast<Action>(actInt);
        Location newLoc = env.Result(loc, act);
        if ((newLoc.x == unback.x) && (newLoc.y == unback.y)) {
          a = act;
          break;
        }
      }
    }
  }
  else {
    a = untried[i].front();
    untried[i].pop_front();
  }
  s = loc;
  return a;
  
}

int main() {

  Environment env;
  
  // initialize untried with lists of Action T (to distinguish empty vs. never used)
  for (int i = 0; i < LENGTH; i++) {
    list<Action> blankList;
    blankList.push_back(T);
    untried[i] = blankList;
  }

  // initialize previous state to null
  s.x = -1;
  s.y = -1;

  // start at location (0,0)
  Location startLoc;
  startLoc.x = 0;
  startLoc.y = 0;

  // perform online DFS until reaching the goal state
  Action ra;
  while (ra != T) {
    ra = onlineDFSAgent(startLoc, env);
    cout << report( ra ) << endl;  
    Location newLoc = env.Result( startLoc, ra ); 
    startLoc = newLoc;
  }

  return 1;
  
}


