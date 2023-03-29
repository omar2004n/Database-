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
void Show_Attr(relation *r,char info);
void Show_Relation(relation *r);
void link_attr(relation * r,attr *at);
void enter_functional_dep(relation *r);
void startscreen(relation *r);
int check_repetitions(attr* tmp,attr *new);
attr * create_attr(char info);
attr *search_attr(relation *r,char info);
void get_def(relation *r,attr *tmp);
int def_len(attr *tmp);
void merge(relation *r,attr *tmp1,attr *tmp2);

int main()
{
    relation *rel=(relation*)malloc(sizeof(relation));
    rel->first=rel->last=NULL;
    startscreen(rel);
    return 0;
}
int check_attr(relation *r,char info)
{
    return (search_attr(r,info)==NULL)?1:0;
}
attr *search_attr(relation *r,char info)
{
    	if(r==NULL){
		printf("\nRelation Doesn't exist\n");
		return NULL;
	}
	if (r->first==NULL){
		printf ("\nEmpty Relation\n");
		return NULL;
	}
    attr *tmp=r->first;
    		while (tmp!= NULL){
            if(tmp->info==info)break;
			tmp = tmp -> next ;
		}
        return tmp;
}
void Show_Attr(relation *r,char info){
	    int i=0;
        //printf("----Showing Attribute '%c'----",info);
	    attr * tmp = NULL;
		tmp= search_attr(r,info);
		if(tmp==NULL){
			printf("\nAttribute not found !");
			return ;
		}
		else {
		printf("\n[ %c:  ",tmp->info);
		while(tmp->def[i]!=NULL)
		{
			printf(" %c, ",tmp->def[i]->info);
			i++;
		}
		printf("]");
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
   tmp =r->first;
   while(tmp != NULL) {
      Show_Attr(r,tmp->info);
      tmp = tmp->next;
   }
   
   
}




attr * create_attr(char info)
{
	attr *at;
    at = (attr*)malloc(sizeof(attr));
    if(at==NULL)exit(404);
    at->info=info;
    at->next=NULL;
    at->def=(attr**)malloc(sizeof(attr)*2);
    at->def[0]=at;
    at->def[1]=NULL;
    return at;
}

void link_attr(relation * r,attr *at)
{
    if(at==NULL||r==NULL)
    {
        printf("\nError !");
        return ;
    }
    if(r->first == NULL)
    {
        r->first=r->last=at;
        at->next=NULL;
        return ;
    }
    
    r->last->next=at;
    at->next=NULL;
    r->last=at;
}

void enter_functional_dep(relation *r)
{
    attr *tmp=r->first,*d=NULL;
    int i=3;
    char c;
    printf("\n--Enter Functional Dependencies (X -> Y) enter '0' if finished--\n");
    while(tmp!=NULL)
    {
        c='1';
        printf("\n%c :\t",tmp->info);
        while(c!='0')
        {
            
            c=getchar();
            getchar();
            d=search_attr(r,c);
            if(d==NULL&&c!='0'){
                printf("\n--Attribut '%c' not found !--",c);
                continue;
            }
            if(check_repetitions(tmp,d))
            continue;
            if(c=='0')
            break;

            tmp->def=(attr**)realloc(tmp->def,i*sizeof(attr*));
            tmp->def[i-2]=d;
            tmp->def[i-1]=NULL;
            i++;
            
        }
        printf("\n----------------------------------------");
        tmp=tmp->next;
        i=3;
    }
}

int  check_repetitions(attr *tmp,attr *new)
{
    int i=0;
    
    while(tmp->def[i]!=NULL)
    {
        if(tmp->def[i]==new)
        return 1;
        i++;
    }
    return 0;
}
int def_len(attr *tmp)
{
    int i=0;
    while(tmp->def[i]!=NULL)i++;
    return i;
}
void merge(relation *r,attr *tmp1,attr *tmp2)
{
    int i=0,j=def_len(tmp1);
    while(i<def_len(tmp2))
    {
        j=def_len(tmp1);
        if(check_repetitions(tmp1,tmp2->def[i]))
        {i++;
        continue ;}
        tmp1->def=(attr **)realloc(tmp1->def,sizeof(attr)*(j+2));
        j+=2;
        tmp1->def[j-1]=NULL;
        tmp1->def[j-2]=tmp2->def[i];
        i++;

    }
    return ;
}
void get_def(relation *r,attr *tmp)
{
   if(r==NULL||tmp==NULL)
    {
        printf("\nEmpty relation or attribute\n");
        return ;
    }
    int i,j;
    attr *t;
    for(i=0;i<def_len(tmp);i++)
        {
            t=tmp->def[i];
            for(j=0;t->def[j]!=NULL;j++)
            {
                merge(r,tmp,t);
            }
        }
}
void startscreen(relation *r)
{
    attr *tmp;
    char c='c';
    int i=0;
    system("clear");
    printf("\nEnter all the attributs (if you're done enter 0) :\n");
    while(c!='0')
    {
        //c='0';
    c=getchar();
    getchar();
    
    if(c!='0'&&c!='\n'&&c!='\t')
    link_attr(r,create_attr(c));
    //else printf("\nInvalid name !");
    }
    c='+';
    system("clear");
    enter_functional_dep(r);
    system("clear");
    while(c!='0')
    {
        printf("\nEnter the attributs to get the closure if (finished enter 0)");
        c =getchar();
        getchar();
        
        if(c=='0')
        break;
        if(tmp==NULL)continue;
        if(i==0)
        tmp=search_attr(r,c);
        merge(r,tmp,search_attr(r,c));
        i++;
    }
    get_def(r,tmp);
    Show_Attr(r,tmp->info);
    //Show_Relation(r);
    
}
