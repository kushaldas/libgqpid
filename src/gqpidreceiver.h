
#include <glib.h>
#include <gqpidmessage.h>


typedef struct _GQpidReceiver GQpidReceiver;
#ifdef __cplusplus
GQpidReceiver*            g_qpid_receiver_new                       (qpid::messaging::Session &, const gchar*);
extern "C" {
#endif
GQpidMessage*                    g_qpid_receiver_fetch              (GQpidReceiver *, int);
#ifdef __cplusplus
}
#endif
