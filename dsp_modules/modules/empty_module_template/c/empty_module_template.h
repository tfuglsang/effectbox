//

#define EMPTY_MODULE_TEMPLATE_MAX_BLOCKSIZE 128

typedef struct {
    float output[EMPTY_MODULE_TEMPLATE_MAX_BLOCKSIZE];
    int blocksize;
    int init_ok;
} t_empty_module_template_data;

/* INTERFACE FUNCTIONS */

int empty_module_template_init(t_empty_module_template_data *empty_module_template_data, int blocksize);
void empty_module_template_reset(t_empty_module_template_data *empty_module_template_data);
void empty_module_template_apply(t_empty_module_template_data *empty_module_template_data, float *input);
