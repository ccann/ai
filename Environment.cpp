/*  Environment.cpp
 *  Created by ablumer on 2/19/13.
 */

#include "Environment.h"

bool Environment::Goal_Test( Location loc ) {
  if (loc.x == LOCSIZE-1 && loc.y == LOCSIZE-1) return true;
  return false;
}

ActStruct Environment::Actions( Location loc ) {
  ActStruct retval;
  retval.N = !Wall[2*loc.x+1][2*loc.y+2];
  retval.S = !Wall[2*loc.x+1][2*loc.y];
  retval.E = !Wall[2*loc.x+2][2*loc.y+1];
  retval.W = !Wall[2*loc.x][2*loc.y+1];
  return retval;
}

Location Environment::Result( Location loc, Action a ) {
  Location retval;
  retval.x = loc.x;
  retval.y = loc.y;
  if (a == N) {
    if (!Wall[2*loc.x+1][2*loc.y+2]) {
	  retval.y += 1;	  
	}
	return retval;
  }
  if (a == S) {
    if (!Wall[2*loc.x+1][2*loc.y]) {
	  retval.y -= 1;	  
	}
	return retval;
  }
  if (a == E) {
    if (!Wall[2*loc.x+2][2*loc.y+1]) {
	  retval.x += 1;	  
	}
	return retval;
  }
  if (a == W) {
    if (!Wall[2*loc.x][2*loc.y+1]) {
	  retval.x -= 1;	  
	}
	return retval;
  }
}

// Initialize the Wall array to "no walls", then put walls around
// the outside, and the four walls shown in Figure 4.19
Environment::Environment() {
  for (int i=0; i<WALLSIZE; i++) {
    for (int j=0; j<WALLSIZE; j++) {
	  Wall[i][j] = false;
    }
  }
  for (int i=1; i<WALLSIZE; i+=2) {
    Wall[0][i] = true;
	Wall[i][0] = true;
    Wall[WALLSIZE-1][i] = true;
	Wall[i][WALLSIZE-1] = true;	
  }
  Wall[1][4] = true;
  Wall[2][3] = true;
  Wall[4][3] = true;
  Wall[4][5] = true;
}