#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <grec.h>

int main() {
    GRec *rec;
    g_type_init();

    rec = g_rec_new();
    g_rec_set_values(rec, 2, 3);
    g_printf("%d\n", g_rec_area(rec));

    return 0;

}
