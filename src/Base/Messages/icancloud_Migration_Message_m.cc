//
// Generated file, do not edit! Created by nedtool 4.6 from src/Base/Messages/icancloud_Migration_Message.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "icancloud_Migration_Message_m.h"

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

icancloud_Migration_Message_Base::icancloud_Migration_Message_Base(const char *name, int kind) : ::icancloud_App_NET_Message(name,kind)
{
    this->memorySizeKB_var = 0;
    this->diskSizeKB_var = 0;
    this->virtualIP_var = "";
    this->remoteStorage_var = false;
    this->standardRequests_var = 0;
    this->deleteRequests_var = 0;
    this->remoteStorageUsedKB_var = 0;
}

icancloud_Migration_Message_Base::icancloud_Migration_Message_Base(const icancloud_Migration_Message_Base& other) : ::icancloud_App_NET_Message(other)
{
    copy(other);
}

icancloud_Migration_Message_Base::~icancloud_Migration_Message_Base()
{
}

icancloud_Migration_Message_Base& icancloud_Migration_Message_Base::operator=(const icancloud_Migration_Message_Base& other)
{
    if (this==&other) return *this;
    ::icancloud_App_NET_Message::operator=(other);
    copy(other);
    return *this;
}

void icancloud_Migration_Message_Base::copy(const icancloud_Migration_Message_Base& other)
{
    this->memorySizeKB_var = other.memorySizeKB_var;
    this->diskSizeKB_var = other.diskSizeKB_var;
    this->virtualIP_var = other.virtualIP_var;
    this->remoteStorage_var = other.remoteStorage_var;
    this->standardRequests_var = other.standardRequests_var;
    this->deleteRequests_var = other.deleteRequests_var;
    this->remoteStorageUsedKB_var = other.remoteStorageUsedKB_var;
}

void icancloud_Migration_Message_Base::parsimPack(cCommBuffer *b)
{
    ::icancloud_App_NET_Message::parsimPack(b);
    doPacking(b,this->memorySizeKB_var);
    doPacking(b,this->diskSizeKB_var);
    doPacking(b,this->virtualIP_var);
    doPacking(b,this->remoteStorage_var);
    doPacking(b,this->standardRequests_var);
    doPacking(b,this->deleteRequests_var);
    doPacking(b,this->remoteStorageUsedKB_var);
}

void icancloud_Migration_Message_Base::parsimUnpack(cCommBuffer *b)
{
    ::icancloud_App_NET_Message::parsimUnpack(b);
    doUnpacking(b,this->memorySizeKB_var);
    doUnpacking(b,this->diskSizeKB_var);
    doUnpacking(b,this->virtualIP_var);
    doUnpacking(b,this->remoteStorage_var);
    doUnpacking(b,this->standardRequests_var);
    doUnpacking(b,this->deleteRequests_var);
    doUnpacking(b,this->remoteStorageUsedKB_var);
}

int icancloud_Migration_Message_Base::getMemorySizeKB() const
{
    return memorySizeKB_var;
}

void icancloud_Migration_Message_Base::setMemorySizeKB(int memorySizeKB)
{
    this->memorySizeKB_var = memorySizeKB;
}

int icancloud_Migration_Message_Base::getDiskSizeKB() const
{
    return diskSizeKB_var;
}

void icancloud_Migration_Message_Base::setDiskSizeKB(int diskSizeKB)
{
    this->diskSizeKB_var = diskSizeKB;
}

const char * icancloud_Migration_Message_Base::getVirtualIP() const
{
    return virtualIP_var.c_str();
}

void icancloud_Migration_Message_Base::setVirtualIP(const char * virtualIP)
{
    this->virtualIP_var = virtualIP;
}

bool icancloud_Migration_Message_Base::getRemoteStorage() const
{
    return remoteStorage_var;
}

void icancloud_Migration_Message_Base::setRemoteStorage(bool remoteStorage)
{
    this->remoteStorage_var = remoteStorage;
}

int icancloud_Migration_Message_Base::getStandardRequests() const
{
    return standardRequests_var;
}

void icancloud_Migration_Message_Base::setStandardRequests(int standardRequests)
{
    this->standardRequests_var = standardRequests;
}

int icancloud_Migration_Message_Base::getDeleteRequests() const
{
    return deleteRequests_var;
}

void icancloud_Migration_Message_Base::setDeleteRequests(int deleteRequests)
{
    this->deleteRequests_var = deleteRequests;
}

int icancloud_Migration_Message_Base::getRemoteStorageUsedKB() const
{
    return remoteStorageUsedKB_var;
}

void icancloud_Migration_Message_Base::setRemoteStorageUsedKB(int remoteStorageUsedKB)
{
    this->remoteStorageUsedKB_var = remoteStorageUsedKB;
}

class icancloud_Migration_MessageDescriptor : public cClassDescriptor
{
  public:
    icancloud_Migration_MessageDescriptor();
    virtual ~icancloud_Migration_MessageDescriptor();

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

Register_ClassDescriptor(icancloud_Migration_MessageDescriptor);

icancloud_Migration_MessageDescriptor::icancloud_Migration_MessageDescriptor() : cClassDescriptor("icancloud_Migration_Message", "icancloud_App_NET_Message")
{
}

icancloud_Migration_MessageDescriptor::~icancloud_Migration_MessageDescriptor()
{
}

bool icancloud_Migration_MessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<icancloud_Migration_Message_Base *>(obj)!=NULL;
}

const char *icancloud_Migration_MessageDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int icancloud_Migration_MessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int icancloud_Migration_MessageDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *icancloud_Migration_MessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "memorySizeKB",
        "diskSizeKB",
        "virtualIP",
        "remoteStorage",
        "standardRequests",
        "deleteRequests",
        "remoteStorageUsedKB",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int icancloud_Migration_MessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "memorySizeKB")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "diskSizeKB")==0) return base+1;
    if (fieldName[0]=='v' && strcmp(fieldName, "virtualIP")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "remoteStorage")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "standardRequests")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "deleteRequests")==0) return base+5;
    if (fieldName[0]=='r' && strcmp(fieldName, "remoteStorageUsedKB")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *icancloud_Migration_MessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "string",
        "bool",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *icancloud_Migration_MessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int icancloud_Migration_MessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    icancloud_Migration_Message_Base *pp = (icancloud_Migration_Message_Base *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string icancloud_Migration_MessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    icancloud_Migration_Message_Base *pp = (icancloud_Migration_Message_Base *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMemorySizeKB());
        case 1: return long2string(pp->getDiskSizeKB());
        case 2: return oppstring2string(pp->getVirtualIP());
        case 3: return bool2string(pp->getRemoteStorage());
        case 4: return long2string(pp->getStandardRequests());
        case 5: return long2string(pp->getDeleteRequests());
        case 6: return long2string(pp->getRemoteStorageUsedKB());
        default: return "";
    }
}

bool icancloud_Migration_MessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    icancloud_Migration_Message_Base *pp = (icancloud_Migration_Message_Base *)object; (void)pp;
    switch (field) {
        case 0: pp->setMemorySizeKB(string2long(value)); return true;
        case 1: pp->setDiskSizeKB(string2long(value)); return true;
        case 2: pp->setVirtualIP((value)); return true;
        case 3: pp->setRemoteStorage(string2bool(value)); return true;
        case 4: pp->setStandardRequests(string2long(value)); return true;
        case 5: pp->setDeleteRequests(string2long(value)); return true;
        case 6: pp->setRemoteStorageUsedKB(string2long(value)); return true;
        default: return false;
    }
}

const char *icancloud_Migration_MessageDescriptor::getFieldStructName(void *object, int field) const
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

void *icancloud_Migration_MessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    icancloud_Migration_Message_Base *pp = (icancloud_Migration_Message_Base *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


