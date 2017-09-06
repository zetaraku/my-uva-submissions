#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#define undefined SIZE_MAX

size_t friend_parent[10000];
size_t enemy[10000];		/* can have at most one enemy per group */

size_t getGroup(size_t x){
	if(friend_parent[x]==x)
		return x;			/* the group leader is found */
	else
		return friend_parent[x] = getGroup(friend_parent[x]);	/* shorten the route! */
}
size_t getEnemy(size_t x){
	size_t x_enemy=enemy[getGroup(x)];
	if(x_enemy!=undefined)		/* WARN: undefined enemy can't use getGroup() */
		x_enemy=getGroup(x_enemy);
	return x_enemy;
}

bool areFriends(size_t x, size_t y){
	return getGroup(x) == getGroup(y);
}
bool areEnemies(size_t x, size_t y){
	return getEnemy(x) == getGroup(y);
}
bool setFriends(size_t x, size_t y){
	size_t gx=getGroup(x), gy=getGroup(y);
	size_t ex=getEnemy(x), ey=getEnemy(y);

	/* signal an error(false) if they contradict with your former knowledge */
	if(areEnemies(x,y))
		return false;
	/* already friends */
	if(areFriends(x,y))
		return true;

	/* shows that x and y are from the same country */
	if(ex==undefined && ey==undefined)
		friend_parent[gy]=gx;	/* no enemy need to be preserved, choose either one */
	else if(ex!=undefined && ey==undefined)
		friend_parent[gy]=gx;	/* the enemy MUST be preserved!! */
	else if(ex==undefined && ey!=undefined)
		friend_parent[gx]=gy;	/* the enemy MUST be preserved!! */
	else if(ex!=undefined && ey!=undefined)
		friend_parent[gy]=gx;	/* the enemies will be merged, choose either one */

	/* A common enemy makes two people friends. */
	if(ex!=undefined && ey!=undefined)
		setFriends(ex,ey);

	return true;
}
bool setEnemies(size_t x, size_t y){
	size_t gx=getGroup(x), gy=getGroup(y);
	size_t ex=getEnemy(x), ey=getEnemy(y);

	/* signal an error(false) if they contradict with your former knowledge */
	if(areFriends(x,y))
		return false;
	/* already enemies */
	if(areEnemies(x,y))
		return true;

	/* shows that x and y are from diﬀerent countries */
	enemy[gx]=gy, enemy[gy]=gx;

	/* A common enemy makes two people friends. (must do first!) */
	if(ex!=undefined)
		setFriends(ex,gy);
	if(ey!=undefined)
		setFriends(gx,ey);

	return true;
}

int main(int argc, char const *argv[]) {	
	size_t number_of_people;
	scanf("%lu",&number_of_people);	/* WARN: the format size '%lu' may differ on different system */

	size_t i; for(i=0;i<number_of_people;i++){
		friend_parent[i]=i;			/* Everyone is a friend of himself. */
		enemy[i]=undefined;			/* Enemy is undefined initially */
	}

	size_t c, x, y;
	while(true){
		int input=scanf("%lu %lu %lu", &c,&x,&y);
		if(c==0||input!=3)
			break;
		else if(c==1)
			setFriends(x,y) || printf("-1\n");
		else if(c==2)
			setEnemies(x,y) || printf("-1\n");
		else if(c==3)
			printf("%d\n", areFriends(x,y));
		else if(c==4)
			printf("%d\n", areEnemies(x,y));
	}
	return 0;
}