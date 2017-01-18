/* Function implementations for ECE 209 Program 4 */
/* Tri Nguyen              */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"

/*
 * Print a single pokemon to stream
 */
void printPokemon(struct pokemon *p, FILE *stream) {
	if (stream == NULL) stream = stdout;
	if (strcmp((*p).type2, "NONE") == 0)
		fprintf ( stream, "%03d %-10s %s/%s", (*p).index, (*p).name, (*p).type1, (*p).type2);
	else 
		fprintf ( stream, "%03d %-10s %s", (*p).index, (*p).name, (*p).type1);

  return;
}

/*
 * Print a single sighting to stream
 */
void printSighting(struct sighting *s, FILE *stream, struct pokemon p[]) {
	struct sighting *point=s;
	if (stream == NULL) stream = stdout;
	fprintf ( stream,"%s %02d:%02d %-10s (%.2f,%.2f) << %s, %s, %.2f >>\n", (*point).date, (*point).hrs, (*point).mins, p[(*point).id].name, (*point).where.latitude, (*point).where.longitude, (*point).timeofday,(*point).weather, (*point).temperature); 
  return;
}  

/*
 * Read all pokemon information from file.
 */
int readPokemon(FILE *stream, struct pokemon p[]) {
	int i=0,a=0,b=0; 
	while((fscanf(stream, "%d %s %s %s %d %d", &p[i].index, p[i].name, p[i].type1, p[i].type2, &a, &b ) != EOF)|| (i>151)){
			i++;
	}
 	return i;
}

/*
 * Read all sighting information from file.
 * Creates new sightings list.
 */
struct sNode * readSightings(FILE *stream, int *n) {
	int i=0; 
	struct sNode *p;
	struct sNode *h;
	struct sNode *new;
	struct sNode *prev;
	new = (struct sNode *) malloc(sizeof(struct sNode));
	h = new; 

	while (fscanf(stream,"%d %lf %lf %s %d:%d %s %s %lf \n", &(*new).s.id, &(*new).s.where.latitude, &(*new).s.where.longitude, (*new).s.date, &(*new).s.hrs, &(*new).s.mins, (*new).s.timeofday, (*new).s.weather, &(*new).s.temperature)  != EOF){	
		p= (struct sNode *) malloc(sizeof(struct sNode));
		new->next = p;
		prev = new;
		new = p;
		i++;
	}
	prev->next=NULL;	
	*n = i;
  return h;
}

/*
 * Sort pokemon array, alphabetically by name.
 */
void sortPokemonByName(struct pokemon p[]) {
	int min, i,j,tmp;
	char temp[11]="aaa";
	for (i=0; i<151;i++){
		min= i;
		for(j=i+1; j <151;j++){
			if (strcmp(p[j].name,p[min].name)<0)
				min = j;
			}
		strcpy(temp,p[i].name); /*exchange name*/
		strcpy(p[i].name,p[min].name);
		strcpy(p[min].name,temp);

		tmp=p[i].index;/*exchange index*/
		p[i].index=p[min].index;
		p[min].index =tmp;

		strcpy(temp,p[i].type1);/*exchange type*/
		strcpy(p[i].type1,p[min].type1);
		strcpy(p[min].type1,temp);
	
		strcpy(temp,p[i].type2);/*exchange type*/
		strcpy(p[i].type2,p[min].type2);
		strcpy(p[min].type2,temp);
	
	}

  return;
}

/*
 * Sort pokemon array, low to high by index.
 */
void sortPokemonByIndex(struct pokemon p[]) {
	int min, i,j,tmp;
	char temp[11]="aaa";

	for (i=0; i<151;i++){
		min= i;
		for(j=i+1; j <151;j++){
			if (p[j].index <p[min].index)
				min = j;
			}
		strcpy(temp,p[i].name); /*exchange name*/
		strcpy(p[i].name,p[min].name);
		strcpy(p[min].name,temp);

		tmp=p[i].index;/*exchange index*/
		p[i].index=p[min].index;
		p[min].index =tmp;

		strcpy(temp,p[i].type1);/*exchange type*/
		strcpy(p[i].type1,p[min].type1);
		strcpy(p[min].type1,temp);
	
		strcpy(temp,p[i].type2);/*exchange type*/
		strcpy(p[i].type2,p[min].type2);
		strcpy(p[min].type2,temp);
	}




  return;
}

/*
 * Sort pokemon array, alphabetically by type.
 */
void sortPokemonByType(struct pokemon p[]) {
	int min, i,j,tmp;
	char temp[11]="aaa";
	for (i=0; i<151;i++){
		min= i;
		for(j=i+1; j <151;j++){
			if (strcmp(p[j].type1,p[min].type1)<0)
				min = j;
			else if ((strcmp(p[j].type1,p[min].type1)==0)&&(strcmp(p[min].type2, "NONE")!=0)&&(strcmp(p[j].type2, "NONE")==0))
				min = j;
			else if ((strcmp(p[j].type1,p[min].type1)==0)&&(strcmp(p[min].type2, "NONE")==0)&&(strcmp(p[j].type2, "NONE")==0)&&(p[j].index <p[min].index))
				min = j;
			else if ((strcmp(p[j].type1,p[min].type1)==0)&&(strcmp(p[min].type2, "NONE")!=0)&&(strcmp(p[j].type2, "NONE")!=0)&&(strcmp(p[j].type2,p[min].type2)<0))
				min = j;
			else if ((strcmp(p[j].type1,p[min].type1)==0)&&(strcmp(p[min].type2, "NONE")!=0)&&(strcmp(p[j].type2, "NONE")!=0)&&(strcmp(p[j].type2,p[min].type2)==0)&&(p[j].index <p[min].index))
				min = j;
		}

		strcpy(temp,p[i].name); /*exchange name*/
		strcpy(p[i].name,p[min].name);
		strcpy(p[min].name,temp);

		tmp=p[i].index;/*exchange index*/
		p[i].index=p[min].index;
		p[min].index =tmp;

		strcpy(temp,p[i].type1);/*exchange type*/
		strcpy(p[i].type1,p[min].type1);
		strcpy(p[min].type1,temp);
	
		strcpy(temp,p[i].type2);/*exchange type*/
		strcpy(p[i].type2,p[min].type2);
		strcpy(p[min].type2,temp);
	}	
  return;
}

/*
 * Print pokemon array, one per line.
 */
void printPokemonArray(struct pokemon p[], FILE *stream) {
	int i; 
	if (stream == NULL) stream = stdout;
	for(i=0; i<151;i++){
	if (strcmp(p[i].type2, "NONE") == 0)
		fprintf ( stream, "%03d %-10s %s \n", p[i].index, p[i].name, p[i].type1);
	else 
		fprintf ( stream, "%03d %-10s %s/%s \n", p[i].index, p[i].name, p[i].type1, p[i].type2);
	}
  return;
}

/*
 * Print sightings list, one per line.
 */
void printSightingList(struct sNode *s, FILE *stream, struct pokemon p[]) {
	struct sNode *point=s;
	if (stream == NULL) stream = stdout;
	while (	point != NULL){
		fprintf ( stream,"%s %02d:%02d %-10s (%.2f,%.2f) << %s, %s, %.2f >>\n", (*point).s.date, (*point).s.hrs, (*point).s.mins, p[(*point).s.id].name, (*point).s.where.latitude, (*point).s.where.longitude, (*point).s.timeofday,(*point).s.weather, (*point).s.temperature); 
		point=point->next;
	}
  return;
}

/*
 * Create new list of sightings that match name.
 * Result list is sorted by date, then time, then time.
 */
struct sNode *findSightingsByName(struct sNode *s, char *name,
				  struct pokemon p[]) {
	int i=0;

	struct sNode *point = s;
	struct sNode *point1;
	struct sNode *point2;
	struct sNode *sorted=NULL;

	while((point!=NULL)&&(i<1)){
		if (strcmp(p[(*point).s.id].name,name)==0){	
			sorted= (struct sNode *) malloc(sizeof(struct sNode));
		sorted->s.id =(*point).s.id;
		sorted->s.where.latitude =point->s.where.latitude ;
		sorted->s.where.longitude =point->s.where.longitude;
		strcpy(sorted->s.date,point->s.date);
		sorted->s.hrs =point->s.hrs;
		sorted->s.mins =point->s.mins;
		strcpy(sorted->s.timeofday,point->s.timeofday);
		strcpy(sorted->s.weather,point->s.weather);
		sorted->s.temperature =point->s.temperature;
		point1=sorted;
		i++;
		}
		point=point->next;
		if ((point==NULL)&&(i=1))
			return NULL;
		 /*find the first element and get the head to point to it*/

	}
	while (	point != NULL){
		if (strcmp(p[(*point).s.id].name,name)==0){
		point2= (struct sNode *) malloc(sizeof(struct sNode));
		sorted->next=point2;
		sorted=point2;
			
		sorted->s.id =point->s.id;
		sorted->s.where.latitude =point->s.where.latitude ;
		sorted->s.where.longitude =point->s.where.longitude;
		strcpy(sorted->s.date,point->s.date);
		sorted->s.hrs =point->s.hrs;
		sorted->s.mins =point->s.mins;
		strcpy(sorted->s.timeofday,point->s.timeofday);
		strcpy(sorted->s.weather,point->s.weather);
		sorted->s.temperature =point->s.temperature;
		}
		point=point->next;
	}
	sorted->next=NULL;



  return point1;
}

/*
 * Create new list of sightings that match type.
 */
struct sNode *findSightingsByType(struct sNode *s, char *type,
				  struct pokemon p[]) {
	int i=0; 
	
	struct sNode *point = s;
	struct sNode *point1;
	struct sNode *point2;
	struct sNode *sorted=NULL;
	while((point!=NULL)&&(i<1)){
		if ((strcmp(p[(*point).s.id].type1,type)==0)||(strcmp(p[(*point).s.id].type2,type)==0)){	
			sorted= (struct sNode *) malloc(sizeof(struct sNode));
		sorted->s.id =(*point).s.id;
		sorted->s.where.latitude =point->s.where.latitude ;
		sorted->s.where.longitude =point->s.where.longitude;
		strcpy(sorted->s.date,point->s.date);
		sorted->s.hrs =point->s.hrs;
		sorted->s.mins =point->s.mins;
		strcpy(sorted->s.timeofday,point->s.timeofday);
		strcpy(sorted->s.weather,point->s.weather);
		sorted->s.temperature =point->s.temperature;
		point1=sorted;
		i++;
		}
		point=point->next;
		if ((point==NULL)&&(i=1))
			return NULL;
		 /*find the first element and get the head to point to it*/

	}
	while (	point != NULL){
		if ((strcmp(p[(*point).s.id].type1,type)==0)||(strcmp(p[(*point).s.id].type2,type)==0)){
		point2= (struct sNode *) malloc(sizeof(struct sNode));
		sorted->next=point2;
		sorted=point2;
			
		sorted->s.id =point->s.id;
		sorted->s.where.latitude =point->s.where.latitude ;
		sorted->s.where.longitude =point->s.where.longitude;
		strcpy(sorted->s.date,point->s.date);
		sorted->s.hrs =point->s.hrs;
		sorted->s.mins =point->s.mins;
		strcpy(sorted->s.timeofday,point->s.timeofday);
		strcpy(sorted->s.weather,point->s.weather);
		sorted->s.temperature =point->s.temperature;
		}
		point=point->next;
	}
	sorted->next=NULL;

  return point1;
}

/*
 * Prints counts for each pokemon sighted, high to low.
 */
void countSightingsByName(struct sNode *s, FILE *stream, struct pokemon p[]) {
  printf("countSightingsByName not implemented\n");
  return;
}

