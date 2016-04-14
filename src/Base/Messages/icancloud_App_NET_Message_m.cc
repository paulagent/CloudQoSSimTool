//
// Generated file, do not edit! Created by nedtool 4.6 from src/Base/Messages/icancloud_App_NET_Message.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "icancloud_App_NET_Message_m.h"

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

icancloud_App_NET_Message_Base::icancloud_App_NET_Message_Base(const char *name, int kind) : ::icancloud_Message(name,kind)
{
    this->destinationIP_var = "";
    this->localIP_var = "";
    this->destinationPort_var = 0;
    this->localPort_var = 0;
    this->connectionType_var = "";
    this->size_var = 0;
    this->data_var = "";
    this->virtual_destinationIP_var = "";
    this->virtual_localIP_var = "";
    this->virtual_user_var = -1;
    this->virtual_destinationPort_var = 0;
    this->virtual_localPort_var = 0;
    this->fsType_var = "";
    this->targetPosition_var = 1;
}

icancloud_App_NET_Message_Base::icancloud_App_NET_Message_Base(const icancloud_App_NET_Message_Base& other) : ::icancloud_Message(other)
{
    copy(other);
}

icancloud_App_NET_Message_Base::~icancloud_App_NET_Message_Base()
{
}

icancloud_App_NET_Message_Base& icancloud_App_NET_Message_Base::operator=(const icancloud_App_NET_Message_Base& other)
{
    if (this==&other) return *this;
    ::icancloud_Message::operator=(other);
    copy(other);
    return *this;
}

void icancloud_App_NET_Message_Base::copy(const icancloud_App_NET_Message_Base& other)
{
    this->destinationIP_var = other.destinationIP_var;
    this->localIP_var = other.localIP_var;
    this->destinationPort_var = other.destinationPort_var;
    this->localPort_var = other.localPort_var;
    this->connectionType_var = other.connectionType_var;
    this->size_var = other.size_var;
    this->data_var = other.data_var;
    this->virtual_destinationIP_var = other.virtual_destinationIP_var;
    this->virtual_localIP_var = other.virtual_localIP_var;
    this->virtual_user_var = other.virtual_user_var;
    this->virtual_destinationPort_var = other.virtual_destinationPort_var;
    this->virtual_localPort_var = other.virtual_localPort_var;
    this->fsType_var = other.fsType_var;
    this->targetPosition_var = other.targetPosition_var;
}

void icancloud_App_NET_Message_Base::parsimPack(cCommBuffer *b)
{
    ::icancloud_Message::parsimPack(b);
    doPacking(b,this->destinationIP_var);
    doPacking(b,this->localIP_var);
    doPacking(b,this->destinationPort_var);
    doPacking(b,this->localPort_var);
    doPacking(b,this->connectionType_var);
    doPacking(b,this->size_var);
    doPacking(b,this->data_var);
    doPacking(b,this->virtual_destinationIP_var);
    doPacking(b,this->virtual_localIP_var);
    doPacking(b,this->virtual_user_var);
    doPacking(b,this->virtual_destinationPort_var);
    doPacking(b,this->virtual_localPort_var);
    doPacking(b,this->fsType_var);
    doPacking(b,this->targetPosition_var);
}

void icancloud_App_NET_Message_Base::parsimUnpack(cCommBuffer *b)
{
    ::icancloud_Message::parsimUnpack(b);
    doUnpacking(b,this->destinationIP_var);
    doUnpacking(b,this->localIP_var);
    doUnpacking(b,this->destinationPort_var);
    doUnpacking(b,this->localPort_var);
    doUnpacking(b,this->connectionType_var);
    doUnpacking(b,this->size_var);
    doUnpacking(b,this->data_var);
    doUnpacking(b,this->virtual_destinationIP_var);
    doUnpacking(b,this->virtual_localIP_var);
    doUnpacking(b,this->virtual_user_var);
    doUnpacking(b,this->virtual_destinationPort_var);
    doUnpacking(b,this->virtual_localPort_var);
    doUnpacking(b,this->fsType_var);
    doUnpacking(b,this->targetPosition_var);
}

const char * icancloud_App_NET_Message_Base::getDestinationIP() const
{
    return destinationIP_var.c_str();
}

void icancloud_App_NET_Message_Base::setDestinationIP(const char * destinationIP)
{
    this->destinationIP_var = destinationIP;
}

const char * icancloud_App_NET_Message_Base::getLocalIP() const
{
    return localIP_var.c_str();
}

void icancloud_App_NET_Message_Base::setLocalIP(const char * localIP)
{
    this->localIP_var = localIP;
}

int icancloud_App_NET_Message_Base::getDestinationPort() const
{
    return destinationPort_var;
}

void icancloud_App_NET_Message_Base::setDestinationPort(int destinationPort)
{
    this->destinationPort_var = destinationPort;
}

int icancloud_App_NET_Message_Base::getLocalPort() const
{
    return localPort_var;
}

void icancloud_App_NET_Message_Base::setLocalPort(int localPort)
{
    this->localPort_var = localPort;
}

const char * icancloud_App_NET_Message_Base::getConnectionType() const
{
    return connectionType_var.c_str();
}

void icancloud_App_NET_Message_Base::setConnectionType(const char * connectionType)
{
    this->connectionType_var = connectionType;
}

unsigned int icancloud_App_NET_Message_Base::getSize() const
{
    return size_var;
}

void icancloud_App_NET_Message_Base::setSize(unsigned int size)
{
    this->size_var = size;
}

const char * icancloud_App_NET_Message_Base::getData() const
{
    return data_var.c_str();
}

void icancloud_App_NET_Message_Base::setData(const char * data)
{
    this->data_var = data;
}

const char * icancloud_App_NET_Message_Base::getVirtual_destinationIP() const
{
    return virtual_destinationIP_var.c_str();
}

void icancloud_App_NET_Message_Base::setVirtual_destinationIP(const char * virtual_destinationIP)
{
    this->virtual_destinationIP_var = virtual_destinationIP;
}

const char * icancloud_App_NET_Message_Base::getVirtual_localIP() const
{
    return virtual_localIP_var.c_str();
}

void icancloud_App_NET_Message_Base::setVirtual_localIP(const char * virtual_localIP)
{
    this->virtual_localIP_var = virtual_localIP;
}

int icancloud_App_NET_Message_Base::getVirtual_user() const
{
    return virtual_user_var;
}

void icancloud_App_NET_Message_Base::setVirtual_user(int virtual_user)
{
    this->virtual_user_var = virtual_user;
}

int icancloud_App_NET_Message_Base::getVirtual_destinationPort() const
{
    return virtual_destinationPort_var;
}

void icancloud_App_NET_Message_Base::setVirtual_destinationPort(int virtual_destinationPort)
{
    this->virtual_destinationPort_var = virtual_destinationPort;
}

int icancloud_App_NET_Message_Base::getVirtual_localPort() const
{
    return virtual_localPort_var;
}

void icancloud_App_NET_Message_Base::setVirtual_localPort(int virtual_localPort)
{
    this->virtual_localPort_var = virtual_localPort;
}

const char * icancloud_App_NET_Message_Base::getFsType() const
{
    return fsType_var.c_str();
}

void icancloud_App_NET_Message_Base::setFsType(const char * fsType)
{
    this->fsType_var = fsType;
}

int icancloud_App_NET_Message_Base::getTargetPosition() const
{
    return targetPosition_var;
}

void icancloud_App_NET_Message_Base::setTargetPosition(int targetPosition)
{
    this->targetPosition_var = targetPosition;
}

class icancloud_App_NET_MessageDescriptor : public cClassDescriptor
{
  public:
    icancloud_App_NET_MessageDescriptor();
    virtual ~icancloud_App_NET_MessageDescriptor();

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

Register_ClassDescriptor(icancloud_App_NET_MessageDescriptor);

icancloud_App_NET_MessageDescriptor::icancloud_App_NET_MessageDescriptor() : cClassDescriptor("icancloud_App_NET_Message", "icancloud_Message")
{
}

icancloud_App_NET_MessageDescriptor::~icancloud_App_NET_MessageDescriptor()
{
}

bool icancloud_App_NET_MessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<icancloud_App_NET_Message_Base *>(obj)!=NULL;
}

const char *icancloud_App_NET_MessageDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int icancloud_App_NET_MessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 14+basedesc->getFieldCount(object) : 14;
}

unsigned int icancloud_App_NET_MessageDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<14) ? fieldTypeFlags[field] : 0;
}

const char *icancloud_App_NET_MessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "destinationIP",
        "localIP",
        "destinationPort",
        "localPort",
        "connectionType",
        "size",
        "data",
        "virtual_destinationIP",
        "virtual_localIP",
        "virtual_user",
        "virtual_destinationPort",
        "virtual_localPort",
        "fsType",
        "targetPosition",
    };
    return (field>=0 && field<14) ? fieldNames[field] : NULL;
}

int icancloud_App_NET_MessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationIP")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "localIP")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationPort")==0) return base+2;
    if (fieldName[0]=='l' && strcmp(fieldName, "localPort")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "connectionType")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "size")==0) return base+5;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+6;
    if (fieldName[0]=='v' && strcmp(fieldName, "virtual_destinationIP")==0) return base+7;
    if (fieldName[0]=='v' && strcmp(fieldName, "virtual_localIP")==0) return base+8;
    if (fieldName[0]=='v' && strcmp(fieldName, "virtual_user")==0) return base+9;
    if (fieldName[0]=='v' && strcmp(fieldName, "virtual_destinationPort")==0) return base+10;
    if (fieldName[0]=='v' && strcmp(fieldName, "virtual_localPort")==0) return base+11;
    if (fieldName[0]=='f' && strcmp(fieldName, "fsType")==0) return base+12;
    if (fieldName[0]=='t' && strcmp(fieldName, "targetPosition")==0) return base+13;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *icancloud_App_NET_MessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "int",
        "int",
        "string",
        "unsigned int",
        "string",
        "string",
        "string",
        "int",
        "int",
        "int",
        "string",
        "int",
    };
    return (field>=0 && field<14) ? fieldTypeStrings[field] : NULL;
}

const char *icancloud_App_NET_MessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int icancloud_App_NET_MessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    icancloud_App_NET_Message_Base *pp = (icancloud_App_NET_Message_Base *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string icancloud_App_NET_MessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    icancloud_App_NET_Message_Base *pp = (icancloud_App_NET_Message_Base *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getDestinationIP());
        case 1: return oppstring2string(pp->getLocalIP());
        case 2: return long2string(pp->getDestinationPort());
        case 3: return long2string(pp->getLocalPort());
        case 4: return oppstring2string(pp->getConnectionType());
        case 5: return ulong2string(pp->getSize());
        case 6: return oppstring2string(pp->getData());
        case 7: return oppstring2string(pp->getVirtual_destinationIP());
        case 8: return oppstring2string(pp->getVirtual_localIP());
        case 9: return long2string(pp->getVirtual_user());
        case 10: return long2string(pp->getVirtual_destinationPort());
        case 11: return long2string(pp->getVirtual_localPort());
        case 12: return oppstring2string(pp->getFsType());
        case 13: return long2string(pp->getTargetPosition());
        default: return "";
    }
}

bool icancloud_App_NET_MessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    icancloud_App_NET_Message_Base *pp = (icancloud_App_NET_Message_Base *)object; (void)pp;
    switch (field) {
        case 0: pp->setDestinationIP((value)); return true;
        case 1: pp->setLocalIP((value)); return true;
        case 2: pp->setDestinationPort(string2long(value)); return true;
        case 3: pp->setLocalPort(string2long(value)); return true;
        case 4: pp->setConnectionType((value)); return true;
        case 5: pp->setSize(string2ulong(value)); return true;
        case 6: pp->setData((value)); return true;
        case 7: pp->setVirtual_destinationIP((value)); return true;
        case 8: pp->setVirtual_localIP((value)); return true;
        case 9: pp->setVirtual_user(string2long(value)); return true;
        case 10: pp->setVirtual_destinationPort(string2long(value)); return true;
        case 11: pp->setVirtual_localPort(string2long(value)); return true;
        case 12: pp->setFsType((value)); return true;
        case 13: pp->setTargetPosition(string2long(value)); return true;
        default: return false;
    }
}

const char *icancloud_App_NET_MessageDescriptor::getFieldStructName(void *object, int field) const
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

void *icancloud_App_NET_MessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    icancloud_App_NET_Message_Base *pp = (icancloud_App_NET_Message_Base *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


