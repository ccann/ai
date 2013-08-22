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
 * SEE figure 4.21 in Russell and Norvig 3e for algorithm OnlineDFSAgent
 * SEE figure 4.19 for environment
 *
 * :TODO: add graphical depiction of state traversal
 *
 */

#include <list>
#include <iostream>
#include <algorithm>

#include "Environment.h"

using namespace std;

// 
#define LENGTH LOCSIZE*LOCSIZE

list<Action> untried[LENGTH];
list<Location> unbacktracked[LENGTH];
Location s;
Action a;
Location result[LENGTH*4];

// returns location as an integer for indexing an array
int locToIndex(Location loc){
  return (loc.x * LOCSIZE) + loc.y;
}

// returns location and action as an integer for indexing an array
int locAcToIndex(Location loc, Action ac){
  return (locToIndex(loc) + (10*ac));
}

// returns the list of available actions from those in an ActStruct
list<Action> getActions(ActStruct ac){
  list<Action> actions;
  if (ac.N == 1){ actions.push_back(N); }
  if (ac.W == 1){ actions.push_back(W); }
  if (ac.S == 1){ actions.push_back(S); }
  if (ac.E == 1){ actions.push_back(E); }
  return actions;
}

// returns the string representation of an action
string reportAction(Action a) {
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

// return the opposite cardinal direction
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
  int i = locToIndex(loc);
  cout << "s': (" << loc.x << "," << loc.y << ") s: (" << s.x << "," << s.y << ") action: " ;

  if (env.Goal_Test(loc)) { // found goal?
    cout << "\nAT GOAL STATE ";
    return T;
  }

  // if list of untried states is empty...
  if (binary_search(untried[i].begin(), untried[i].end(), T)) { 
    untried[i] = getActions(env.Actions(loc)); 
    untried[i].remove(getOppositeAction(a));
  }

  // if previous state not null...
  if (s.x != -1) { 
    result[locAcToIndex(s, a)] = loc;
    unbacktracked[i].push_back(s);
  }

  // if all actions have been tried for this state...
  if (untried[i].empty()) {
    // if all previous states have been backtracked...
    if (unbacktracked[i].empty()) {
      return T;
    }
    // otherwise take action that backtracks to previous state
    else { 
      Location unback = unbacktracked[i].front();
      unbacktracked[i].pop_front();
      for (int actInt = N; actInt != T; actInt++) {
        Action act = static_cast<Action>(actInt);
        Location t = result[locAcToIndex(unback, act)];
        if ((t.x == loc.x) && (t.y == loc.y)) {
          a = getOppositeAction(act);
          break;            
        }
      }
    }
  }

  // otherwise try the next untried action
  else {
    a = untried[i].front();
    untried[i].pop_front();
  }

  s = loc;  // set previous state to current state
  return a; 
  
}

int main() {

  Environment env;
  Location startLoc;
  startLoc.x = 0;
  startLoc.y = 0;

  // initialize untried with lists of T (to distinguish empty vs. never used)
  for (int i = 0; i < LENGTH; i++) {
    list<Action> blankList;
    blankList.push_back(T);
    untried[i] = blankList;
  }

  // initialize previous state to null
  s.x = -1;
  s.y = -1;

  // initialize members of result array to null location
  for (int i = 0; i < LENGTH*4; i++){
    result[i] = s;
  }

  // perform online DFS until reaching the goal state
  Action action;
  while (action != T) {
    action = onlineDFSAgent(startLoc, env);
    cout << reportAction( action ) << endl;  
    startLoc = env.Result( startLoc, action ); 
  }

  return 1;
}


