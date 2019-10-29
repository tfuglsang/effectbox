#include <empty_module_template/c/empty_module_template.h>
//#include "empty_module_template.h" // remove this line when you have inserted this module in modules.h

int empty_module_template_init(t_empty_module_template_data *empty_module_template_data, int blocksize) {
    // error handling
    empty_module_template_data->init_ok = 0;
    if (blocksize>EMPTY_MODULE_TEMPLATE_MAX_BLOCKSIZE) return 1;
    // no errors, go on..
    empty_module_template_data->blocksize = blocksize;
    empty_module_template_reset(empty_module_template_data);
    empty_module_template_data->init_ok = 1;
    return 0;
}

void empty_module_template_reset(t_empty_module_template_data *empty_module_template_data) {
    const int bs = empty_module_template_data->blocksize;
    for (int i=0; i<bs; i++) empty_module_template_data->output[i] = 0.0f;
}

void empty_module_template_apply(t_empty_module_template_data *empty_module_template_data, float *input) {
    // error?
    if (!empty_module_template_data->init_ok) return;
    // no, go on...
    const int bs = empty_module_template_data->blocksize;
    for (int i=0; i<bs; i++) empty_module_template_data->output[i] = input[i];
}
