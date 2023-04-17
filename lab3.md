* * ```
    // Lab 3-1 Extra
    struct Signal {
        u_int num;
        struct Env_list wait_queue;
    };
    
    static struct Signal S[3];
    
    void S_init(int s, int num) {
        S[s].num = num;
        LIST_INIT(&(S[s].wait_queue));
    }
    
    int is_in_waitqueue(struct Env* e, int s) {
        struct Env *i; 
        LIST_FOREACH(i, &(S[s].wait_queue), env_link) {
            if (i == e) return 1;
        }   
        return 0;
    }
    
    void Add(struct Env *e, int s) {
        if (s == 1) ++e->have1;
        else if(s == 2) ++e->have2;
    }
    
    void Sub(struct Env *e, int s) {
        if (s == 1 && e->have1 > 0) --e->have1;
        else if (s == 2 && e->have2 > 0) --e->have2;
    }
    
    int P(struct Env* e, int s) {    
        if (is_in_waitqueue(e, 1) || is_in_waitqueue(e, 2)) return -1;
        if (S[s].num > 0) {
            Add(e, s);
            S[s].num--;
            return 0;
        } else {
            LIST_INSERT_TAIL(&(S[s].wait_queue), e, env_link);
            return 0;
        }
    }
    
    int V(struct Env* e, int s) {
        if (is_in_waitqueue(e, 1) || is_in_waitqueue(e, 2)) return -1;
        else {
            S[s].num++;
            Sub(e, s);
            if (S[s].num > 0) {
                if (!LIST_EMPTY(&(S[s].wait_queue))) {
                    struct Env * new_env = LIST_FIRST(&(S[s].wait_queue));
                    LIST_REMOVE(new_env, env_link);
                    Add(new_env, s);
                    S[s].num--;
                }
            }
        }
        return 0;
    }
    
    int get_status(struct Env* e) {
        if (is_in_waitqueue(e, 1) || is_in_waitqueue(e, 2)) return 1;
        if (e->have1 == 0 && e->have2 == 0) return 3;
        else return 2;
    }
    
    int my_env_create() {
        struct Env *e;
    
        if (LIST_EMPTY(&env_free_list)) {
            return -1;
        }
        e = LIST_FIRST(&env_free_list);
        e->env_id = mkenvid(e);
        e->env_status = ENV_RUNNABLE;
        
        e->env_tf.cp0_status = 0x10001004;
        e->env_tf.regs[29] = USTACKTOP;
    
        LIST_REMOVE(e, env_link);
        e->have2 = e->have1 = 0;
        return e->env_id;
    }
    ```

    