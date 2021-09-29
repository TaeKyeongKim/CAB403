#include <pthread.h>
#include <stdint.h> 

#define ENTRANCE 5
#define EXIT 5
#define LEVEL 5
#define CAPACITY 100



typedef struct LPR{
    pthread_mutex_t mutex_lock;
    pthread_cond_t condition_variable;
    char * license_plate[6];
} LPR_t;

typedef struct boom_gate{
    pthread_mutex_t mutex_lock;
    pthread_cond_t condition_variable;
    char *status;    
} boom_gate_t;

typedef struct info_sign{
    pthread_mutex_t mutex_lock;
    pthread_cond_t condition_variable;
    char * display;
} info_sign_t;


typedef struct tem_sensor{
    
    int16_t *curr_temp;
  
} tem_sensor_t;

typedef struct alarm{
    
    char state; 
  
} alarm_t;
  


typedef struct entrances{
    // License plate recognition sensor 
    LPR_t * LPR; 
    boom_gate_t* boom_gate;
    info_sign_t* info_sign;


} entrances_t;

typedef struct exits {
    // License plate recognition sensor 
    LPR_t * LPR; 
    boom_gate_t* boom_gate;


} exits_t;


typedef struct levels {
    // License plate recognition sensor 
    LPR_t* LPR; 
    tem_sensor_t* tem_sensor;
    alarm_t * alarm;
    
    

} levels_t;


/**
 * A shared memory control structure.
 */
typedef struct PARKING {
     /// Address of the shared memory bytes for entrances . 
    entrances_t* entrances[ENTRANCE];
    exits_t* exits[EXIT];
    levels_t* levels[LEVEL];

   
} PARKING_t;
