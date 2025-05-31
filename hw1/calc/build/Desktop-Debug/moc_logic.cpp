/****************************************************************************
** Meta object code from reading C++ file 'logic.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../logic.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Logic_t {
    QByteArrayData data[23];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Logic_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Logic_t qt_meta_stringdata_Logic = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Logic"
QT_MOC_LITERAL(1, 6, 9), // "onChanged"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 6), // "turnOn"
QT_MOC_LITERAL(4, 24, 7), // "turnOff"
QT_MOC_LITERAL(5, 32, 6), // "input0"
QT_MOC_LITERAL(6, 39, 6), // "input1"
QT_MOC_LITERAL(7, 46, 6), // "input2"
QT_MOC_LITERAL(8, 53, 6), // "input3"
QT_MOC_LITERAL(9, 60, 6), // "input4"
QT_MOC_LITERAL(10, 67, 6), // "input5"
QT_MOC_LITERAL(11, 74, 6), // "input6"
QT_MOC_LITERAL(12, 81, 6), // "input7"
QT_MOC_LITERAL(13, 88, 6), // "input8"
QT_MOC_LITERAL(14, 95, 6), // "input9"
QT_MOC_LITERAL(15, 102, 7), // "input00"
QT_MOC_LITERAL(16, 110, 8), // "inputDot"
QT_MOC_LITERAL(17, 119, 6), // "delDig"
QT_MOC_LITERAL(18, 126, 6), // "chSign"
QT_MOC_LITERAL(19, 133, 4), // "mult"
QT_MOC_LITERAL(20, 138, 3), // "add"
QT_MOC_LITERAL(21, 142, 3), // "div"
QT_MOC_LITERAL(22, 146, 3) // "sub"

    },
    "Logic\0onChanged\0\0turnOn\0turnOff\0input0\0"
    "input1\0input2\0input3\0input4\0input5\0"
    "input6\0input7\0input8\0input9\0input00\0"
    "inputDot\0delDig\0chSign\0mult\0add\0div\0"
    "sub"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Logic[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  120,    2, 0x0a /* Public */,
       4,    0,  121,    2, 0x0a /* Public */,
       5,    0,  122,    2, 0x0a /* Public */,
       6,    0,  123,    2, 0x0a /* Public */,
       7,    0,  124,    2, 0x0a /* Public */,
       8,    0,  125,    2, 0x0a /* Public */,
       9,    0,  126,    2, 0x0a /* Public */,
      10,    0,  127,    2, 0x0a /* Public */,
      11,    0,  128,    2, 0x0a /* Public */,
      12,    0,  129,    2, 0x0a /* Public */,
      13,    0,  130,    2, 0x0a /* Public */,
      14,    0,  131,    2, 0x0a /* Public */,
      15,    0,  132,    2, 0x0a /* Public */,
      16,    0,  133,    2, 0x0a /* Public */,
      17,    0,  134,    2, 0x0a /* Public */,
      18,    0,  135,    2, 0x0a /* Public */,
      19,    0,  136,    2, 0x0a /* Public */,
      20,    0,  137,    2, 0x0a /* Public */,
      21,    0,  138,    2, 0x0a /* Public */,
      22,    0,  139,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::QString,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Logic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Logic *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { QString _r = _t->onChanged();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->turnOn(); break;
        case 2: _t->turnOff(); break;
        case 3: _t->input0(); break;
        case 4: _t->input1(); break;
        case 5: _t->input2(); break;
        case 6: _t->input3(); break;
        case 7: _t->input4(); break;
        case 8: _t->input5(); break;
        case 9: _t->input6(); break;
        case 10: _t->input7(); break;
        case 11: _t->input8(); break;
        case 12: _t->input9(); break;
        case 13: _t->input00(); break;
        case 14: _t->inputDot(); break;
        case 15: _t->delDig(); break;
        case 16: _t->chSign(); break;
        case 17: _t->mult(); break;
        case 18: _t->add(); break;
        case 19: _t->div(); break;
        case 20: _t->sub(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = QString (Logic::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Logic::onChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Logic::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Logic.data,
    qt_meta_data_Logic,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Logic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Logic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Logic.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Logic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
QString Logic::onChanged()
{
    QString _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
