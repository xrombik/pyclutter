#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <cairo/cairo.h>
#include <pycairo.h>
#include <clutter/clutter.h>
#include <clutter-cairo/clutter-cairo.h>

void pycluttercairo_register_classes (PyObject *d);
extern PyMethodDef pycluttercairo_functions[];

Pycairo_CAPI_t *Pycairo_CAPI;

DL_EXPORT(void)
init_cluttercairo (void)
{
  PyObject *m, *d;
    
  init_pygobject ();
    
  Pycairo_IMPORT;
  if (Pycairo_CAPI == NULL)
    return;

  /* perform any initialisation required by the library here */

  m = Py_InitModule ("_cluttercairo", pycluttercairo_functions);
  d = PyModule_GetDict (m);

  pycluttercairo_register_classes (d);

  if (PyErr_Occurred ())
    Py_FatalError ("unable to initialise cluttercairo module");
}
