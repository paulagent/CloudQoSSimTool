//
// Generated file, do not edit! Created by nedtool 4.6 from src/Base/Messages/icancloud_App_IO_Message.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "icancloud_App_IO_Message_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

icancloud_App_IO_Message_Base::icancloud_App_IO_Message_Base(const char *name, int kind) : ::icancloud_Message(name,kind)
{
    this->fileName_var = "";
    this->offset_var = 0;
    this->size_var = 0;
    this->isPending_var = false;
    this->nfs_destAddress_var = "";
    this->nfs_destPort_var = - 1;
    this->nfs_id_var = - 1;
    this->nfs_type_var = "";
    this->nfs_requestSize_KB_var = -1;
    this->nfs_connectionID_var = -1;
}

icancloud_App_IO_Message_Base::icancloud_App_IO_Message_Base(const icancloud_App_IO_Message_Base& other) : ::icancloud_Message(other)
{
    copy(other);
}

icancloud_App_IO_Message_Base::~icancloud_App_IO_Message_Base()
{
}

icancloud_App_IO_Message_Base& icancloud_App_IO_Message_Base::operator=(const icancloud_App_IO_Message_Base& other)
{
    if (this==&other) return *this;
    ::icancloud_Message::operator=(other);
    copy(other);
    return *this;
}

void icancloud_App_IO_Message_Base::copy(const icancloud_App_IO_Message_Base& other)
{
    this->fileName_var = other.fileName_var;
    this->offset_var = other.offset_var;
    this->size_var = other.size_var;
    this->isPending_var = other.isPending_var;
    this->nfs_destAddress_var = other.nfs_destAddress_var;
    this->nfs_destPort_var = other.nfs_destPort_var;
    this->nfs_id_var = other.nfs_id_var;
    this->nfs_type_var = other.nfs_type_var;
    this->nfs_requestSize_KB_var = other.nfs_requestSize_KB_var;
    this->nfs_connectionID_var = other.nfs_connectionID_var;
}

void icancloud_App_IO_Message_Base::parsimPack(cCommBuffer *b)
{
    ::icancloud_Message::parsimPack(b);
    doPacking(b,this->fileName_var);
    doPacking(b,this->offset_var);
    doPacking(b,this->size_var);
    doPacking(b,this->isPending_var);
    doPacking(b,this->nfs_destAddress_var);
    doPacking(b,this->nfs_destPort_var);
    doPacking(b,this->nfs_id_var);
    doPacking(b,this->nfs_type_var);
    doPacking(b,this->nfs_requestSize_KB_var);
    doPacking(b,this->nfs_connectionID_var);
}

void icancloud_App_IO_Message_Base::parsimUnpack(cCommBuffer *b)
{
    ::icancloud_Message::parsimUnpack(b);
    doUnpacking(b,this->fileName_var);
    doUnpacking(b,this->offset_var);
    doUnpacking(b,this->size_var);
    doUnpacking(b,this->isPending_var);
    doUnpacking(b,this->nfs_destAddress_var);
    doUnpacking(b,this->nfs_destPort_var);
    doUnpacking(b,this->nfs_id_var);
    doUnpacking(b,this->nfs_type_var);
    doUnpacking(b,this->nfs_requestSize_KB_var);
    doUnpacking(b,this->nfs_connectionID_var);
}

const char * icancloud_App_IO_Message_Base::getFileName() const
{
    return fileName_var.c_str();
}

void icancloud_App_IO_Message_Base::setFileName(const char * fileName)
{
    this->fileName_var = fileName;
}

unsigned int icancloud_App_IO_Message_Base::getOffset() const
{
    return offset_var;
}

void icancloud_App_IO_Message_Base::setOffset(unsigned int offset)
{
    this->offset_var = offset;
}

unsigned int icancloud_App_IO_Message_Base::getSize() const
{
    return size_var;
}

void icancloud_App_IO_Message_Base::setSize(unsigned int size)
{
    this->size_var = size;
}

bool icancloud_App_IO_Message_Base::getIsPending() const
{
    return isPending_var;
}

void icancloud_App_IO_Message_Base::setIsPending(bool isPending)
{
    this->isPending_var = isPending;
}

const char * icancloud_App_IO_Message_Base::getNfs_destAddress() const
{
    return nfs_destAddress_var.c_str();
}

void icancloud_App_IO_Message_Base::setNfs_destAddress(const char * nfs_destAddress)
{
    this->nfs_destAddress_var = nfs_destAddress;
}

int icancloud_App_IO_Message_Base::getNfs_destPort() const
{
    return nfs_destPort_var;
}

void icancloud_App_IO_Message_Base::setNfs_destPort(int nfs_destPort)
{
    this->nfs_destPort_var = nfs_destPort;
}

int icancloud_App_IO_Message_Base::getNfs_id() const
{
    return nfs_id_var;
}

void icancloud_App_IO_Message_Base::setNfs_id(int nfs_id)
{
    this->nfs_id_var = nfs_id;
}

const char * icancloud_App_IO_Message_Base::getNfs_type() const
{
    return nfs_type_var.c_str();
}

void icancloud_App_IO_Message_Base::setNfs_type(const char * nfs_type)
{
    this->nfs_type_var = nfs_type;
}

int icancloud_App_IO_Message_Base::getNfs_requestSize_KB() const
{
    return nfs_requestSize_KB_var;
}

void icancloud_App_IO_Message_Base::setNfs_requestSize_KB(int nfs_requestSize_KB)
{
    this->nfs_requestSize_KB_var = nfs_requestSize_KB;
}

int icancloud_App_IO_Message_Base::getNfs_connectionID() const
{
    return nfs_connectionID_var;
}

void icancloud_App_IO_Message_Base::setNfs_connectionID(int nfs_connectionID)
{
    this->nfs_connectionID_var = nfs_connectionID;
}

class icancloud_App_IO_MessageDescriptor : public cClassDescriptor
{
  public:
    icancloud_App_IO_MessageDescriptor();
    virtual ~icancloud_App_IO_MessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(icancloud_App_IO_MessageDescriptor);

icancloud_App_IO_MessageDescriptor::icancloud_App_IO_MessageDescriptor() : cClassDescriptor("icancloud_App_IO_Message", "icancloud_Message")
{
}

icancloud_App_IO_MessageDescriptor::~icancloud_App_IO_MessageDescriptor()
{
}

bool icancloud_App_IO_MessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<icancloud_App_IO_Message_Base *>(obj)!=NULL;
}

const char *icancloud_App_IO_MessageDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int icancloud_App_IO_MessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount(object) : 10;
}

unsigned int icancloud_App_IO_MessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *icancloud_App_IO_MessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "fileName",
        "offset",
        "size",
        "isPending",
        "nfs_destAddress",
        "nfs_destPort",
        "nfs_id",
        "nfs_type",
        "nfs_requestSize_KB",
        "nfs_connectionID",
    };
    return (field>=0 && field<10) ? fieldNames[field] : NULL;
}

int icancloud_App_IO_MessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "fileName")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "offset")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "size")==0) return base+2;
    if (fieldName[0]=='i' && strcmp(fieldName, "isPending")==0) return base+3;
    if (fieldName[0]=='n' && strcmp(fieldName, "nfs_destAddress")==0) return base+4;
    if (fieldName[0]=='n' && strcmp(fieldName, "nfs_destPort")==0) return base+5;
    if (fieldName[0]=='n' && strcmp(fieldName, "nfs_id")==0) return base+6;
    if (fieldName[0]=='n' && strcmp(fieldName, "nfs_type")==0) return base+7;
    if (fieldName[0]=='n' && strcmp(fieldName, "nfs_requestSize_KB")==0) return base+8;
    if (fieldName[0]=='n' && strcmp(fieldName, "nfs_connectionID")==0) return base+9;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *icancloud_App_IO_MessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "unsigned int",
        "unsigned int",
        "bool",
        "string",
        "int",
        "int",
        "string",
        "int",
        "int",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : NULL;
}

const char *icancloud_App_IO_MessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int icancloud_App_IO_MessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    icancloud_App_IO_Message_Base *pp = (icancloud_App_IO_Message_Base *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string icancloud_App_IO_MessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    icancloud_App_IO_Message_Base *pp = (icancloud_App_IO_Message_Base *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getFileName());
        case 1: return ulong2string(pp->getOffset());
        case 2: return ulong2string(pp->getSize());
        case 3: return bool2string(pp->getIsPending());
        case 4: return oppstring2string(pp->getNfs_destAddress());
        case 5: return long2string(pp->getNfs_destPort());
        case 6: return long2string(pp->getNfs_id());
        case 7: return oppstring2string(pp->getNfs_type());
        case 8: return long2string(pp->getNfs_requestSize_KB());
        case 9: return long2string(pp->getNfs_connectionID());
        default: return "";
    }
}

bool icancloud_App_IO_MessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    icancloud_App_IO_Message_Base *pp = (icancloud_App_IO_Message_Base *)object; (void)pp;
    switch (field) {
        case 0: pp->setFileName((value)); return true;
        case 1: pp->setOffset(string2ulong(value)); return true;
        case 2: pp->setSize(string2ulong(value)); return true;
        case 3: pp->setIsPending(string2bool(value)); return true;
        case 4: pp->setNfs_destAddress((value)); return true;
        case 5: pp->setNfs_destPort(string2long(value)); return true;
        case 6: pp->setNfs_id(string2long(value)); return true;
        case 7: pp->setNfs_type((value)); return true;
        case 8: pp->setNfs_requestSize_KB(string2long(value)); return true;
        case 9: pp->setNfs_connectionID(string2long(value)); return true;
        default: return false;
    }
}

const char *icancloud_App_IO_MessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *icancloud_App_IO_MessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    icancloud_App_IO_Message_Base *pp = (icancloud_App_IO_Message_Base *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


