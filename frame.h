#ifndef _FRAME_H_
#define _FRAME_H_
#include "pthread.h"
#include "assert.h"
struct frame_t{
    int i_frame ;
    int width ;
    int height ;
    char *data ;
} ;
struct frame_list_t{
    struct frame_t **list ;
    int i_max_size ;
    int i_size ;
    pthread_mutex_t mutex ;
    pthread_cond_t cond_empty ;
    pthread_cond_t cond_full ;
};
struct frame_t *new_frame(int iframe,int iwidth,int iheight) ;
void delete_frame(struct frame_t *frame) ;
int init_frame_list(struct frame_list_t *list,int max_size) ;
void delete_frame_list(struct frame_list_t *list) ;
void push_frame_list(struct frame_list_t *list,struct frame_t *frame) ;
struct frame_t *pop_frame_list(struct frame_list_t *list) ;
#endif
