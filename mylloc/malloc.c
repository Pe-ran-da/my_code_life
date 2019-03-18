#include "malloc.h"

typedef struct __metadata {
    size_t size;
    size_t free;
    struct __metadata *next;
    struct __metadata *prev;
    void *begin;
} MetaData, *pMetaData;

static pMetaData __memory_head = NULL;

static void initMetaData(pMetaData p, size_t size, size_t free, pMetaData prev, pMetaData next) {
    p->size = size;
    p->free = free;
    p->prev = prev;
    p->next = next;
    p->begin = ((char *)p) + sizeof(MetaData);
}


void *mylloc(size_t sizes){
    pMetaData p, q;
    size_t newsize = sizes + sizeof(MetaData);
    if (__memory_head == NULL) {
        p = (pMetaData)sbrk(0);
        if (sbrk(newsize) == (void *)-1) {
            return NULL;
        }
        initMetaData(p, sizes, 0, NULL, NULL);
        __memory_head = p;
    } else {
        p = __memory_head;
        while (p) {
            if (p->free && p->size >= newsize) {
                q = (pMetaData)(((char *)p->begin) + sizes);
                initMetaData(q, p->size - newsize, 1, p, p->next);
                p->size = sizes;
                if (p->next != NULL) {
                    p->next->prev = q;
                }
                p->next = q;
                p->free = 0;
                break;
            } else if (p->free && p->size >= sizes) {
                p->free = 0;
                break;
            }
            if (p->next == NULL) break;
            p = p->next;
        }

        if (p->next == NULL) {
            q = sbrk(0);
            if (sbrk(newsize) == (void *) -1) {
                return NULL;
            }
            initMetaData(q, sizes, 0, p, NULL);
            p->next = q;
            p = p->next;
        }
    }
    return p->begin;
}


void myfree(void *p){
    pMetaData q, w;
    q = (pMetaData ) (((char *)p) - sizeof(MetaData));
    q->free = 1;
    if (q->next != NULL && q->next->free) {
        //当前块和下一块为空闲
        w = q->next->next;
        q->size += q->next->size + sizeof(MetaData);
        if (w) w->prev = q;
        q->next = w;
    }
    if (q->prev != NULL &&q->prev->free) {
        //当前块和前一块
        w = q->next;
        pMetaData e;
        e = q->prev;
        e->size += q->size + sizeof(MetaData);
        if (w) w->prev = e;
        e->next = w;
        //q = e;
    }
    if (q->next == NULL) {
        //sbrk(-(q->size + sizeof(MetaData))); /*此处先删除是错误的*/
        if (q->prev == NULL) __memory_head = NULL;
        else {
            q->prev->next = NULL;
        }
        /*此处q还是q,没有因为上面的操作丢失地址*/
        sbrk(-(q->size + sizeof(MetaData)));
    }
}


void *mycalloc(size_t numitems, size_t size){
    void *temp = mylloc(numitems * size);
    if (temp == NULL) return NULL;
    char *p = (char *)temp;
    size_t len = numitems * size;
    for (size_t i = 0; i < len; i++) {
        p[i] = 0;
    }
    return temp;
}

void dataCopy(void *str, void *new_str, size_t len) {
    size_t i = 0;
    if (str == NULL || new_str == NULL) fflush(stdout);
    char *p1 = (char *)str;
    char *p2 = (char *)new_str;
    while (i < len) {
        p1[i] = p2[i];
        i += 1;
    }
    return ;
}


void *myrealloc(void *ptr, size_t size){
    pMetaData p, q, k;
    p = (pMetaData)(((char *)ptr) - sizeof(MetaData));
    if (p->size >= size) return p->begin;
    if (p->next == NULL) {
        if (sbrk(size - p->size) == (void *)-1) {
            return NULL;
        }
        p->size = size;
    }
    if (p->size < size && p->next && p->next->free) {
        if (p->size + p->next->size >= size) {
            q = (pMetaData)(((char *)p->begin) + size);
            initMetaData(q, p->size + p->next->size - size, 1, p, p->next->next);
            p->next = q;
            p->size = size;
        } else if (p->size + p->next->size + sizeof(MetaData) >= size) {
            p->size = p->size + p->next->size + sizeof(MetaData);
            q = p->next->next;
            p->next = q;
            if (q != NULL) {
                q->prev = p;
            }
            p->size = size;
        }
    }
    if (p->size < size && p->prev && p->prev->free) {
        if (p->size + p->prev->size >= size) {
            q = p->next;
            p = p->prev;
            size_t ksize = p->size + p->next->size - size;
            dataCopy(p->begin, p->next->begin, p->next->size);
            k = (pMetaData)(((char *)p->begin) + size);
            initMetaData(k, ksize, 1, p, q);
            p->next = k;
            if (q != NULL) {
                q->prev = k;
            }
            p->size = size;
            p->free = 0;
        } else if (p->size + p->prev->size + sizeof(MetaData) >= size) {
            q = p->next;
            p = p->prev;
            size_t totalsize = p->size + p->next->size + sizeof(MetaData);
            dataCopy(p->begin, p->next->begin, p->next->size);
            p->next = q;
            if (q != NULL) {
                q->prev = p;
            }
            p->size = totalsize;
            p->free = 0;
        }
    }
    if (p->size < size) {
        void *ret = mylloc(size);
        if (ret == NULL) return NULL;
        dataCopy(ret, p->begin, p->size);
        myfree(p->begin);
        p = (pMetaData)(((char *)ret) - sizeof(MetaData));
    }
    return p->begin;
}


//int main() {
    /*char *buff = mylloc(10);
    if (buff == NULL) {
        printf("NULL\n");
    }
    buff = "ans";
    printf("buff %s\n", buff);
    printf("buff %p\n", buff);
   // myfree(buff);
    buff = mycalloc(30, sizeof(char));
    printf("buff %p\n", buff);
    char *a = mycalloc(10, sizeof(char));
    printf("a %p\n", a);
    a = "number";
    //char *buff = mylloc(10);
    //buff = "a?";


    char *ans = mylloc(10);
    ans = "ans"; 
    printf("ans %p\n", ans);
    printf("a : %s\n", a);
    printf("ans %s\n", ans);
    */
/*    char *buffer = mylloc( 10);
    buffer = "hahah";
    printf("%s\n", buffer);
    myfree(buffer);
    return 0;
}*/
