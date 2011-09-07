
#include <glib.h>
#include <gqpidsession.h>


typedef struct _GQpidConnection GQpidConnection;
#ifdef __cplusplus
extern "C" {
#endif
GQpidConnection*        g_qpid_connection_new                   (gchar* broker);
void                    g_qpid_connection_open                  (GQpidConnection   *conn);
GQpidSession*           g_qpid_connection_create_session        (GQpidConnection   *conn);
void                    g_qpid_connection_close                 (GQpidConnection   *conn);
#ifdef __cplusplus
}
#endif
