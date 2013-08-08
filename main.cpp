#include <iostream>
#include "frame.h"
using namespace std ;

int main()
{
    struct frame_list_t *list = (struct frame_list_t*)malloc(sizeof(struct frame_list_t)) ;
    init_frame_list(list,100) ;
    struct frame_t *frame = NULL;
    for(int i=0;i<50;i++){
        frame = new_frame(i,640,480) ;
        push_frame_list(list,frame) ;
    }
    for(int i=0 ; i<50 ;i++){
        frame = pop_frame_list(list) ;
        cout<<"frame id:"<<frame->i_frame<<endl ;
    }
    delete_frame_list(list) ;
    cout<<list->i_max_size<<endl ;
    cout<<"hello world"<<endl ;
    return 0 ;
}
