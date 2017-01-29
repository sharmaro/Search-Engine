/****************************************************************************
** Meta object code from reading C++ file 'front_end.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "front_end.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'front_end.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrontEnd[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      24,    9,   19,    9, 0x08,
      53,    9,    9,    9, 0x08,
      60,    9,    9,    9, 0x08,
      69,    9,    9,    9, 0x08,
      85,    9,    9,    9, 0x08,
      99,    9,    9,    9, 0x08,
     118,    9,    9,    9, 0x08,
     138,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FrontEnd[] = {
    "FrontEnd\0\0search()\0bool\0"
    "buttonChecked(QRadioButton*)\0quit()\0"
    "update()\0openWindow(int)\0reSortLinks()\0"
    "inLinkClicked(int)\0outLinkClicked(int)\0"
    "closeWindow()\0"
};

void FrontEnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FrontEnd *_t = static_cast<FrontEnd *>(_o);
        switch (_id) {
        case 0: _t->search(); break;
        case 1: { bool _r = _t->buttonChecked((*reinterpret_cast< QRadioButton*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->quit(); break;
        case 3: _t->update(); break;
        case 4: _t->openWindow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->reSortLinks(); break;
        case 6: _t->inLinkClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->outLinkClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->closeWindow(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FrontEnd::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FrontEnd::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FrontEnd,
      qt_meta_data_FrontEnd, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrontEnd::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrontEnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrontEnd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrontEnd))
        return static_cast<void*>(const_cast< FrontEnd*>(this));
    return QWidget::qt_metacast(_clname);
}

int FrontEnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
