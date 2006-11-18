#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pyclutter.h"

struct _PyClutterCallback
{
        PyGObject *caller;

        PyObject *func;
        PyObject *data;
};

PyClutterCallback *
pyclutter_callback_new (PyGObject *caller,
                        PyObject  *func,
                        PyObject  *data)
{
        PyClutterCallback *retval;

        retval = g_slice_new (PyClutterCallback);
        retval->caller = caller;
        retval->func = func;
        retval->data = data;

        Py_INCREF (retval->func);
        Py_XINCREF (retval->data);

        return retval;
}

void
pyclutter_callback_free (PyClutterCallback *cb)
{
        if (G_LIKELY (cb)) {
                Py_DECREF (cb->func);
                Py_XDECREF (cb->data);

                g_slice_free (PyClutterCallback, cb);
        }
}

PyObject *
pyclutter_callback_invoke (PyClutterCallback *cb,
                           PyObject          *caller)
{
        PyObject *retobj;

        if (!cb) {
                g_warning ("Invalid callback set");
                return NULL;
        }

        if (!caller) {
                caller = pygobject_new (G_OBJECT (cb->caller));
        }

        if (cb->data) {
                retobj = PyObject_CallFunction (cb->func, "(NO)",
                                                caller,
                                                cb->data);
        }
        else {
                retobj = PyObject_CallFunction (cb->func, "(N)",
                                                caller);
        }

        return retobj;
}