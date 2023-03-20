#include<stdio.h>
#include<stdlib.h>


typedef struct attr{
    char info;
     struct attr *next;
   struct attr **def;
}attr;

typedef struct relation{
    attr *first;
    attr *last;
}relation;

//show_att();
void Show_Attr(relation *r,char info){
	int i=0;
	if(r==NULL){
		printf("\nRelation Doesn't exist\n");
		return ;
	}
	if (r->first==NULL){
		printf ("\nEmpty Relation\n");
		return ;
	}
	attr * tmp = r->first;

		while (tmp!= NULL||tmp->info==info){
			tmp = tmp -> next ;
		}
		if(tmp==NULL){
			printf("\nAttribute not found");
			return ;
		}
		else {
		printf("\n%c:\t ",tmp->info);
		while(tmp->def[i+1]!=NULL)
		{
			printf(" %c, ",tmp->def[i]->info);
			i++;
		}
		printf("%c",tmp->def[i]->info);
		}
		
	
	
}
//show_relation();
void Show_Relation(relation *r){

   attr *tmp = r->first;
   printf("R(");
   while(tmp != NULL) {
      printf("%c ,", tmp->info);
      tmp = tmp->next;
   }
   printf(")\n");
}




attr * create_attr(char info)
{
	attr *at;
    at = (attr*)malloc(sizeof(attr));
    at->info=info;
    at->next=NULL;
    at->def=(attr**)malloc(sizeof(attr));
    at->def[0]=at;
    return at;
}

void link_attr(relation * r,attr *at)
{
    if(r->first == NULL)
    {
        r->first=r->last=at;
        at->next=NULL;
        return ;
    }
    else {
    	r->last->next=at;
    at->next=NULL;
    r->last=at;
	}
    

}
void startscreen(relation *r)
{
    char c='c';
    system("cls");
    printf("\nEnter all the attributs (if you're done enter 0) :\n");
    while(c!='0')
    {
        //c='0';
    scanf("%c",&c);
    if(c!='0')
    link_attr(r,create_attr(c));
    
    }
	Show_Attr(r,'a');
}
int main()
{
    relation *rel=(relation*)malloc(sizeof(relation));
    rel->first=rel->last=NULL;
    startscreen(rel);
    return 0;
}
