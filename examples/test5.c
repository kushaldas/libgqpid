#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gqpid.h>

void print_hash (GHashTable *);

static gpointer _g_hash_table_ref0 (gpointer self) {
            return self ? g_hash_table_ref (self) : NULL;
}

void print_list(GList *list)
{
    g_printf ("Printing Value types in C in list\n");

    while (1)
    {
        GValue *value = (GValue*) list->data;

        g_printf( "%s\n", G_VALUE_TYPE_NAME (value));
        if ( strcmp("gchararray", G_VALUE_TYPE_NAME (value)) == 0)
            g_printf ("Value: %s\n",  g_value_get_string (value));
        if ( strcmp("gdouble", G_VALUE_TYPE_NAME (value)) == 0)
            g_printf ("Value: %f\n",  g_value_get_double (value));
        if ( strcmp("gint64", G_VALUE_TYPE_NAME (value)) == 0)
            g_printf ("Value: %d\n",  g_value_get_int64 (value));
        if ( strcmp("gboolean", G_VALUE_TYPE_NAME (value)) == 0)
            g_printf ("Value: %d\n", g_value_get_boolean (value));
        if ( strcmp("GHashTable", G_VALUE_TYPE_NAME (value)) == 0)
        {
            GHashTable* h = _g_hash_table_ref0 (g_value_get_boxed (value));
            print_hash (h);
        }
        if ( strcmp("gpointer", G_VALUE_TYPE_NAME (value)) == 0)
        {
            GList* l = g_value_get_pointer (value);
            print_list (l);
        }

        if (list->next == NULL)
            break;
        list = list->next;
    }

}

void print_hash (GHashTable *hash)
{
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hash);
    g_printf ("Printing Value types in C\n");

    while (g_hash_table_iter_next (&iter, &key, &value))
    {
        /* do something with key and value */
        g_printf( "%s\n", G_VALUE_TYPE_NAME (value));
        if ( strcmp("gchararray", G_VALUE_TYPE_NAME (value)) == 0)
            g_printf ("Key: %s Value: %s\n", (gchar*)key, g_value_get_string (value));
        if ( strcmp("gdouble", G_VALUE_TYPE_NAME (value)) == 0)
            g_printf ("Key: %s Value: %f\n", (gchar*)key, g_value_get_double (value));
        if ( strcmp("gint64", G_VALUE_TYPE_NAME (value)) == 0)
            g_printf ("Key: %s Value: %d\n", (gchar*)key, g_value_get_int64 (value));
        if ( strcmp("gboolean", G_VALUE_TYPE_NAME (value)) == 0)
            g_printf ("Key: %s Value: %d\n", (gchar*)key, g_value_get_boolean (value));
        if ( strcmp("GHashTable", G_VALUE_TYPE_NAME (value)) == 0)
        {
            GHashTable* h = _g_hash_table_ref0 (g_value_get_boxed (value));
            print_hash (h);
        }
        if ( strcmp("gpointer", G_VALUE_TYPE_NAME (value)) == 0)
        {
            GList* l = g_value_get_pointer (value);
            print_list (l);
        }
    }

}

int main() {
    GQpidConnection *conn;
    GQpidSession *ses;
    GQpidSender *sender;
    GQpidReceiver *receiver;
    GQpidMessage *msg1;
    GQpidMessage *msg2;
    GHashTable *hash;
    g_type_init();

    conn = g_qpid_connection_new ("localhost:5672");
    g_qpid_connection_open (conn);
    g_printf("%d\n",g_qpid_connection_is_open (conn));

    ses = g_qpid_connection_create_session (conn);

    receiver = g_qpid_session_create_receiver (ses, "amq.topic");


    msg2 = g_qpid_receiver_fetch(receiver, -1);
    g_printf("%s\n", g_qpid_message_get_subject(msg2));
    g_printf("%s\n", g_qpid_message_get_userid(msg2));
    g_printf("%d\n", g_qpid_message_get_priority(msg2));

    hash = g_qpid_message_get_hashtable(msg2);

    print_hash (hash);

    /*g_qpid_session_acknowledge (ses);*/

    /* g_hash_table_unref (hash); */
    g_qpid_session_close (ses);
    g_qpid_session_free (ses);
    g_qpid_connection_close (conn);
    g_qpid_connection_free(conn);

    return 0;

}
