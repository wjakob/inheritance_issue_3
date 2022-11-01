#include <Python.h>
#include <structmember.h>

static PyModuleDef my_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "inheritance_issue_3",
    .m_doc = "Reproducer for an issue involving type inheritance",
    .m_size = -1,
};

static struct PyMemberDef my_property_members[] = {
     { "__dictoffset__", T_PYSSIZET, 0, READONLY, NULL },
     { NULL, 0, 0, 0, NULL }
 };

static PyType_Slot my_property_slots[] = {
    { Py_tp_base, NULL },
    { Py_tp_members, my_property_members },
    { 0, NULL }
};

static PyType_Spec my_property_spec = {
    .name = "inheritance_issue_3.my_property",
    .flags = Py_TPFLAGS_DEFAULT,
    .slots = my_property_slots
};

PyMODINIT_FUNC
PyInit_inheritance_issue_3(void)
{
    PyObject *m = PyModule_Create(&my_module);
    if (m == NULL)
        return NULL;

    my_property_slots[0].pfunc = &PyProperty_Type;
    my_property_spec.basicsize = PyProperty_Type.tp_basicsize + sizeof(PyObject *);
    my_property_members[0].offset = PyProperty_Type.tp_basicsize;

    PyObject *my_property = PyType_FromSpec(&my_property_spec);

    if (PyModule_AddObject(m, "my_property", my_property) < 0) {
        Py_DECREF(my_property);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
