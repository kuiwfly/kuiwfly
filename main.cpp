#include <iostream>
#include "frame.h"
using namespace std ;

int main()
{
    struct frame_list_t *list = (struct frame_list_t*)malloc(sizeof(struct frame_list_t)) ;
    init_frame_list(list,100) ;
    cout<<list->i_max_size<<endl ;
    cout<<"hello world"<<endl ;
    return 0 ;
}
