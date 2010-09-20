#include <boost/python.hpp>
#include <boost/python/exception_translator.hpp>
#include <iostream>
#include "yaz4py.h"

using namespace boost::python;
using namespace std;


PyObject *cppZExceptionType = NULL;
PyObject *cppZQueryExceptionType = NULL;
PyObject *cppZResultSetExceptionType = NULL;
PyObject *cppZConnectionExceptionType = NULL;

//Трансляторы исключений
void translatorZException(ZException const& err) {
    boost::python::object pythonExceptionInstance(err);
    PyErr_SetObject(cppZExceptionType, incref(pythonExceptionInstance.ptr()));
}

void translatorZQueryException(ZQueryException const& err) {
    boost::python::object pythonExceptionInstance(err);
    PyErr_SetObject(cppZQueryExceptionType, incref(pythonExceptionInstance.ptr()));
}

void translatorZResultSetException(ZResultSetException const& err) {
    boost::python::object pythonExceptionInstance(err);
    PyErr_SetObject(cppZResultSetExceptionType, incref(pythonExceptionInstance.ptr()));
}

void translatorZConnectionException(ZConnectionException const& err) {
    boost::python::object pythonExceptionInstance(err);
    PyErr_SetObject(cppZConnectionExceptionType, incref(pythonExceptionInstance.ptr()));
}

BOOST_PYTHON_MODULE(libyaz4pyboost)
{
    //Исключения транслируемые в питон
    //есть проблема с наследованием, т.е. исключение нельзя поймать родителем
    //!надо как-то решить!
    boost::python::class_<ZException>
        ZExceptionClass("ZException",
            boost::python::init<const string&, const int>())
    ;
    ZExceptionClass.add_property("message", &ZException::getMessage);
    ZExceptionClass.add_property("__str__", &ZException::getMessage);
    ZExceptionClass.add_property("code", &ZException::getCode);

    cppZExceptionType = ZExceptionClass.ptr();
    boost::python::register_exception_translator<ZException>
            (&translatorZException)
    ;

    ///////////////////////////////////////////////////////////////////////////
    boost::python::class_<ZQueryException, bases<ZException> >
        ZQueryExceptionClass("ZQueryException",
            boost::python::init<const string&, const int>())
    ;
    ZQueryExceptionClass.add_property("message", &ZQueryException::getMessage);
    ZQueryExceptionClass.add_property("__str__", &ZQueryException::getMessage);
    ZQueryExceptionClass.add_property("code", &ZQueryException::getCode);

    cppZQueryExceptionType = ZQueryExceptionClass.ptr();
    boost::python::register_exception_translator<ZQueryException>
            (&translatorZQueryException)
    ;
    ///////////////////////////////////////////////////////////////////////////
    boost::python::class_<ZResultSetException, bases<ZException> >
        ZResultSetExceptionClass("ZResultSetException",
            boost::python::init<const string&, const int>())
    ;
    ZResultSetExceptionClass.add_property("message", &ZResultSetException::getMessage);
    ZResultSetExceptionClass.add_property("__str__", &ZResultSetException::getMessage);
    ZResultSetExceptionClass.add_property("code", &ZResultSetException::getCode);

    cppZResultSetExceptionType = ZResultSetExceptionClass.ptr();
    boost::python::register_exception_translator<ZResultSetException>
            (&translatorZResultSetException)
    ;
    ///////////////////////////////////////////////////////////////////////////
    boost::python::class_<ZConnectionException, bases<ZException> >
        ZConnectionExceptionClass("ZConnectionException",
            boost::python::init<const string&, const int>())
    ;
    ZConnectionExceptionClass.add_property("message", &ZConnectionException::getMessage);
    ZConnectionExceptionClass.add_property("__str__", &ZConnectionException::getMessage);
    ZConnectionExceptionClass.add_property("code", &ZConnectionException::getCode);

    cppZConnectionExceptionType = ZConnectionExceptionClass.ptr();
    boost::python::register_exception_translator<ZConnectionException>
            (&translatorZConnectionException)
    ;

    ////////////////////////////////////////////////////////////////////////////
    class_<ZOptions>("ZOptions")
        .def("setOption", &ZOptions::setOption)
        .def("setImplementationName", &ZOptions::setImplementationName)
        .def("setUser", &ZOptions::setUser)
        .def("setPassword", &ZOptions::setPassword)
        .def("setDatabase", &ZOptions::setDatabase)
        .def("setCharset", &ZOptions::setCharset)
        .def("setGroup", &ZOptions::setGroup)
        .def("setSyntax", &ZOptions::setSyntax)
        .def("setElementSetName", &ZOptions::setElementSetName)
    ;

    class_<ZConnection>("ZConnection")
        .def(init<const ZOptions *>())
        .def("connect", &ZConnection::connect)
        .def("search", &ZConnection::search, return_value_policy<manage_new_object>())
    ;

    class_<ZQuery>("ZQuery", init<const string &>())
    ;

    class_<ZRecord>("ZRecord", init<ZResultSet*, int>())
        .def("render", &ZRecord::render)
        .def("raw", &ZRecord::raw)
    ;
    
    class_<ZResultSet>("ZResultSet", init<ZConnection *, const ZQuery&>())
        .def("setOption", &ZResultSet::setOption)
        .def("getSize", &ZResultSet::getSize)
        .def("getRecord", &ZResultSet::getRecord, return_value_policy<manage_new_object>())
        .def("setSetName", &ZResultSet::setSetName)
        .def("setSchema", &ZResultSet::setSchema)
    ;
}