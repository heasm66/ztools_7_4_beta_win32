#ifdef __STDC__
void init_symbols (const char *fname);

int print_attribute_name (unsigned long attr_names_base, int attr_no);

int print_property_name (unsigned long property_names_base, int prop_no);

int print_local_name (unsigned long start_of_routine, int local_no);

int print_global_name (unsigned long start_of_routine, int global_no);

int get_global_type (unsigned long start_of_routine, int global_no);

int get_local_type (unsigned long start_of_routine, int local_no);
#endif
