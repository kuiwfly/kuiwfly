#include "frame.h"
struct frame_t *new_frame(int iframe,int iwidth,int iheight){
    struct frame_t *frame = (struct frame_t *)malloc(sizeof(struct frame_t)) ;
    assert(frame!=NULL) ;
    frame->i_frame = iframe ;
    frame->width = iwidth ;
    frame->height = iheight ;
    frame->data = (char*)malloc(iwidth*iheight*sizeof(char)) ;
    assert(frame->data!=NULL) ;
    return frame ;
}
void delete_frame(struct frame_t *frame) {
    assert(frame!=NULL&&frame->data!=NULL) ;
    free(frame->data) ;
    free(frame) ;
}
int init_frame_list(struct frame_list_t *list,int max_size){
    if(max_size<0){
        return -1 ;
    }
    list->i_max_size = max_size ;
    list->i_size = 0 ;
    list->list = (struct frame_t **)malloc(sizeof(struct frame_t*)*(max_size+1)) ;
    if(pthread_mutex_init(&list->mutex,NULL)||
       pthread_cond_init(&list->cond_empty,NULL)||
       pthread_cond_init(&list->cond_full,NULL)){
        return -1 ;
    }else{
        return 0 ;
    }
}
void delete_frame_list(struct frame_list_t *list) {
    assert(list!=NULL) ;
    int i = 0 ;
    pthread_mutex_destroy(&list->mutex) ;
    pthread_cond_destroy(&list->cond_empty) ;
    pthread_cond_destroy(&list->cond_full) ;

    while(list->list[i]){
        delete_frame((list->list[i++])) ;
    }
    free(list->list) ;
    list->list = NULL ;
}
void push_frame_list(struct frame_list_t *list,struct frame_t *frame) {
    pthread_mutex_lock(&list->mutex) ;
    while(list->i_size == list->i_max_size){
        pthread_cond_wait(&list->cond_empty,&list->mutex) ;
    }
    list->list[list->i_size++] = frame ;
    pthread_mutex_unlock(&list->mutex) ;
    pthread_cond_broadcast(&list->cond_full) ;
}
struct frame_t *pop_frame_list(struct frame_list_t *list){
    struct frame_t *frame = NULL ;
    pthread_mutex_lock(&list->mutex) ;
    while(list->i_size == 0){
        pthread_cond_wait(&list->cond_full,&list->mutex) ;
    }
    frame = list->list[--list->i_size] ;
    list->list[list->i_size] = NULL ;
    pthread_mutex_unlock(&list->mutex) ;
    pthread_cond_broadcast(&list->cond_empty) ;
    return frame ;
}
