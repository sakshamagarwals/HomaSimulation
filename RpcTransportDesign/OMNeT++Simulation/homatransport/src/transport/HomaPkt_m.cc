//
// Generated file, do not edit! Created by nedtool 4.6 from HomaPkt.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "HomaPkt_m.h"

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

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("PktType");
    if (!e) enums.getInstance()->add(e = new cEnum("PktType"));
    e->insert(REQUEST, "REQUEST");
    e->insert(GRANT, "GRANT");
    e->insert(SCHED_DATA, "SCHED_DATA");
    e->insert(UNSCHED_DATA, "UNSCHED_DATA");
    e->insert(HOMA_ACK, "HOMA_ACK");
);

UnschedFields::UnschedFields()
{
    msgByteLen = 0;
    msgCreationTime = 0;
    totalUnschedBytes = 0;
    firstByte = 0;
    lastByte = 0;
}

void doPacking(cCommBuffer *b, UnschedFields& a)
{
    doPacking(b,a.msgByteLen);
    doPacking(b,a.msgCreationTime);
    doPacking(b,a.totalUnschedBytes);
    doPacking(b,a.firstByte);
    doPacking(b,a.lastByte);
    doPacking(b,a.prioUnschedBytes);
}

void doUnpacking(cCommBuffer *b, UnschedFields& a)
{
    doUnpacking(b,a.msgByteLen);
    doUnpacking(b,a.msgCreationTime);
    doUnpacking(b,a.totalUnschedBytes);
    doUnpacking(b,a.firstByte);
    doUnpacking(b,a.lastByte);
    doUnpacking(b,a.prioUnschedBytes);
}

class UnschedFieldsDescriptor : public cClassDescriptor
{
  public:
    UnschedFieldsDescriptor();
    virtual ~UnschedFieldsDescriptor();

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

Register_ClassDescriptor(UnschedFieldsDescriptor);

UnschedFieldsDescriptor::UnschedFieldsDescriptor() : cClassDescriptor("UnschedFields", "")
{
}

UnschedFieldsDescriptor::~UnschedFieldsDescriptor()
{
}

bool UnschedFieldsDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<UnschedFields *>(obj)!=NULL;
}

const char *UnschedFieldsDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UnschedFieldsDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int UnschedFieldsDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *UnschedFieldsDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "msgByteLen",
        "msgCreationTime",
        "totalUnschedBytes",
        "firstByte",
        "lastByte",
        "prioUnschedBytes",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int UnschedFieldsDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgByteLen")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgCreationTime")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "totalUnschedBytes")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "firstByte")==0) return base+3;
    if (fieldName[0]=='l' && strcmp(fieldName, "lastByte")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "prioUnschedBytes")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *UnschedFieldsDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",
        "simtime_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "UnsignedVec",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *UnschedFieldsDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int UnschedFieldsDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UnschedFields *pp = (UnschedFields *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string UnschedFieldsDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    UnschedFields *pp = (UnschedFields *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->msgByteLen);
        case 1: return double2string(pp->msgCreationTime);
        case 2: return ulong2string(pp->totalUnschedBytes);
        case 3: return ulong2string(pp->firstByte);
        case 4: return ulong2string(pp->lastByte);
        case 5: {std::stringstream out; out << pp->prioUnschedBytes; return out.str();}
        default: return "";
    }
}

bool UnschedFieldsDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UnschedFields *pp = (UnschedFields *)object; (void)pp;
    switch (field) {
        case 0: pp->msgByteLen = string2ulong(value); return true;
        case 1: pp->msgCreationTime = string2double(value); return true;
        case 2: pp->totalUnschedBytes = string2ulong(value); return true;
        case 3: pp->firstByte = string2ulong(value); return true;
        case 4: pp->lastByte = string2ulong(value); return true;
        default: return false;
    }
}

const char *UnschedFieldsDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 5: return opp_typename(typeid(UnsignedVec));
        default: return NULL;
    };
}

void *UnschedFieldsDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UnschedFields *pp = (UnschedFields *)object; (void)pp;
    switch (field) {
        case 5: return (void *)(&pp->prioUnschedBytes); break;
        default: return NULL;
    }
}

GrantFields::GrantFields()
{
    grantBytes = 0;
    offset = 0;
    schedPrio = 0;
    remainingSize = 0;
}

void doPacking(cCommBuffer *b, GrantFields& a)
{
    doPacking(b,a.grantBytes);
    doPacking(b,a.offset);
    doPacking(b,a.schedPrio);
    doPacking(b,a.sizeReqBytesPrio);
    doPacking(b,a.sizeUnschedBytesPrio);
    doPacking(b,a.remainingSize);
}

void doUnpacking(cCommBuffer *b, GrantFields& a)
{
    doUnpacking(b,a.grantBytes);
    doUnpacking(b,a.offset);
    doUnpacking(b,a.schedPrio);
    doUnpacking(b,a.sizeReqBytesPrio);
    doUnpacking(b,a.sizeUnschedBytesPrio);
    doUnpacking(b,a.remainingSize);
}

class GrantFieldsDescriptor : public cClassDescriptor
{
  public:
    GrantFieldsDescriptor();
    virtual ~GrantFieldsDescriptor();

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

Register_ClassDescriptor(GrantFieldsDescriptor);

GrantFieldsDescriptor::GrantFieldsDescriptor() : cClassDescriptor("GrantFields", "")
{
}

GrantFieldsDescriptor::~GrantFieldsDescriptor()
{
}

bool GrantFieldsDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GrantFields *>(obj)!=NULL;
}

const char *GrantFieldsDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GrantFieldsDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int GrantFieldsDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *GrantFieldsDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "grantBytes",
        "offset",
        "schedPrio",
        "sizeReqBytesPrio",
        "sizeUnschedBytesPrio",
        "remainingSize",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int GrantFieldsDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "grantBytes")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "offset")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "schedPrio")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "sizeReqBytesPrio")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "sizeUnschedBytesPrio")==0) return base+4;
    if (fieldName[0]=='r' && strcmp(fieldName, "remainingSize")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GrantFieldsDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",
        "uint32_t",
        "uint16_t",
        "UnsignedVec",
        "UnsignedVec",
        "uint32_t",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *GrantFieldsDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int GrantFieldsDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GrantFields *pp = (GrantFields *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GrantFieldsDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GrantFields *pp = (GrantFields *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->grantBytes);
        case 1: return ulong2string(pp->offset);
        case 2: return ulong2string(pp->schedPrio);
        case 3: {std::stringstream out; out << pp->sizeReqBytesPrio; return out.str();}
        case 4: {std::stringstream out; out << pp->sizeUnschedBytesPrio; return out.str();}
        case 5: return ulong2string(pp->remainingSize);
        default: return "";
    }
}

bool GrantFieldsDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GrantFields *pp = (GrantFields *)object; (void)pp;
    switch (field) {
        case 0: pp->grantBytes = string2ulong(value); return true;
        case 1: pp->offset = string2ulong(value); return true;
        case 2: pp->schedPrio = string2ulong(value); return true;
        case 5: pp->remainingSize = string2ulong(value); return true;
        default: return false;
    }
}

const char *GrantFieldsDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 3: return opp_typename(typeid(UnsignedVec));
        case 4: return opp_typename(typeid(UnsignedVec));
        default: return NULL;
    };
}

void *GrantFieldsDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GrantFields *pp = (GrantFields *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->sizeReqBytesPrio); break;
        case 4: return (void *)(&pp->sizeUnschedBytesPrio); break;
        default: return NULL;
    }
}

SchedDataFields::SchedDataFields()
{
    firstByte = 0;
    lastByte = 0;
}

void doPacking(cCommBuffer *b, SchedDataFields& a)
{
    doPacking(b,a.firstByte);
    doPacking(b,a.lastByte);
}

void doUnpacking(cCommBuffer *b, SchedDataFields& a)
{
    doUnpacking(b,a.firstByte);
    doUnpacking(b,a.lastByte);
}

class SchedDataFieldsDescriptor : public cClassDescriptor
{
  public:
    SchedDataFieldsDescriptor();
    virtual ~SchedDataFieldsDescriptor();

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

Register_ClassDescriptor(SchedDataFieldsDescriptor);

SchedDataFieldsDescriptor::SchedDataFieldsDescriptor() : cClassDescriptor("SchedDataFields", "")
{
}

SchedDataFieldsDescriptor::~SchedDataFieldsDescriptor()
{
}

bool SchedDataFieldsDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SchedDataFields *>(obj)!=NULL;
}

const char *SchedDataFieldsDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SchedDataFieldsDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int SchedDataFieldsDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *SchedDataFieldsDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "firstByte",
        "lastByte",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int SchedDataFieldsDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "firstByte")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "lastByte")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SchedDataFieldsDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",
        "uint32_t",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *SchedDataFieldsDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SchedDataFieldsDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SchedDataFields *pp = (SchedDataFields *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SchedDataFieldsDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SchedDataFields *pp = (SchedDataFields *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->firstByte);
        case 1: return ulong2string(pp->lastByte);
        default: return "";
    }
}

bool SchedDataFieldsDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SchedDataFields *pp = (SchedDataFields *)object; (void)pp;
    switch (field) {
        case 0: pp->firstByte = string2ulong(value); return true;
        case 1: pp->lastByte = string2ulong(value); return true;
        default: return false;
    }
}

const char *SchedDataFieldsDescriptor::getFieldStructName(void *object, int field) const
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

void *SchedDataFieldsDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SchedDataFields *pp = (SchedDataFields *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

HomaPkt_Base::HomaPkt_Base(const char *name, int kind) : ::cPacket(name,kind)
{
    this->msgId_var = 0;
    this->priority_var = 1;
    this->pktType_var = 0;
}

HomaPkt_Base::HomaPkt_Base(const HomaPkt_Base& other) : ::cPacket(other)
{
    copy(other);
}

HomaPkt_Base::~HomaPkt_Base()
{
}

HomaPkt_Base& HomaPkt_Base::operator=(const HomaPkt_Base& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void HomaPkt_Base::copy(const HomaPkt_Base& other)
{
    this->srcAddr_var = other.srcAddr_var;
    this->destAddr_var = other.destAddr_var;
    this->msgId_var = other.msgId_var;
    this->priority_var = other.priority_var;
    this->pktType_var = other.pktType_var;
    this->unschedFields_var = other.unschedFields_var;
    this->grantFields_var = other.grantFields_var;
    this->schedDataFields_var = other.schedDataFields_var;
}

void HomaPkt_Base::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->srcAddr_var);
    doPacking(b,this->destAddr_var);
    doPacking(b,this->msgId_var);
    doPacking(b,this->priority_var);
    doPacking(b,this->pktType_var);
    doPacking(b,this->unschedFields_var);
    doPacking(b,this->grantFields_var);
    doPacking(b,this->schedDataFields_var);
}

void HomaPkt_Base::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->srcAddr_var);
    doUnpacking(b,this->destAddr_var);
    doUnpacking(b,this->msgId_var);
    doUnpacking(b,this->priority_var);
    doUnpacking(b,this->pktType_var);
    doUnpacking(b,this->unschedFields_var);
    doUnpacking(b,this->grantFields_var);
    doUnpacking(b,this->schedDataFields_var);
}

inet::L3Address& HomaPkt_Base::getSrcAddr()
{
    return srcAddr_var;
}

void HomaPkt_Base::setSrcAddr(const inet::L3Address& srcAddr)
{
    this->srcAddr_var = srcAddr;
}

inet::L3Address& HomaPkt_Base::getDestAddr()
{
    return destAddr_var;
}

void HomaPkt_Base::setDestAddr(const inet::L3Address& destAddr)
{
    this->destAddr_var = destAddr;
}

uint64_t HomaPkt_Base::getMsgId() const
{
    return msgId_var;
}

void HomaPkt_Base::setMsgId(uint64_t msgId)
{
    this->msgId_var = msgId;
}

uint32_t HomaPkt_Base::getPriority() const
{
    return priority_var;
}

void HomaPkt_Base::setPriority(uint32_t priority)
{
    this->priority_var = priority;
}

int HomaPkt_Base::getPktType() const
{
    return pktType_var;
}

void HomaPkt_Base::setPktType(int pktType)
{
    this->pktType_var = pktType;
}

UnschedFields& HomaPkt_Base::getUnschedFields()
{
    return unschedFields_var;
}

void HomaPkt_Base::setUnschedFields(const UnschedFields& unschedFields)
{
    this->unschedFields_var = unschedFields;
}

GrantFields& HomaPkt_Base::getGrantFields()
{
    return grantFields_var;
}

void HomaPkt_Base::setGrantFields(const GrantFields& grantFields)
{
    this->grantFields_var = grantFields;
}

SchedDataFields& HomaPkt_Base::getSchedDataFields()
{
    return schedDataFields_var;
}

void HomaPkt_Base::setSchedDataFields(const SchedDataFields& schedDataFields)
{
    this->schedDataFields_var = schedDataFields;
}

class HomaPktDescriptor : public cClassDescriptor
{
  public:
    HomaPktDescriptor();
    virtual ~HomaPktDescriptor();

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

Register_ClassDescriptor(HomaPktDescriptor);

HomaPktDescriptor::HomaPktDescriptor() : cClassDescriptor("HomaPkt", "cPacket")
{
}

HomaPktDescriptor::~HomaPktDescriptor()
{
}

bool HomaPktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<HomaPkt_Base *>(obj)!=NULL;
}

const char *HomaPktDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int HomaPktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int HomaPktDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *HomaPktDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "srcAddr",
        "destAddr",
        "msgId",
        "priority",
        "pktType",
        "unschedFields",
        "grantFields",
        "schedDataFields",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int HomaPktDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddr")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddr")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgId")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktType")==0) return base+4;
    if (fieldName[0]=='u' && strcmp(fieldName, "unschedFields")==0) return base+5;
    if (fieldName[0]=='g' && strcmp(fieldName, "grantFields")==0) return base+6;
    if (fieldName[0]=='s' && strcmp(fieldName, "schedDataFields")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *HomaPktDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",
        "inet::L3Address",
        "uint64_t",
        "uint32_t",
        "int",
        "UnschedFields",
        "GrantFields",
        "SchedDataFields",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *HomaPktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4:
            if (!strcmp(propertyname,"enum")) return "PktType";
            return NULL;
        default: return NULL;
    }
}

int HomaPktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    HomaPkt_Base *pp = (HomaPkt_Base *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string HomaPktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    HomaPkt_Base *pp = (HomaPkt_Base *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSrcAddr(); return out.str();}
        case 1: {std::stringstream out; out << pp->getDestAddr(); return out.str();}
        case 2: return uint642string(pp->getMsgId());
        case 3: return ulong2string(pp->getPriority());
        case 4: return long2string(pp->getPktType());
        case 5: {std::stringstream out; out << pp->getUnschedFields(); return out.str();}
        case 6: {std::stringstream out; out << pp->getGrantFields(); return out.str();}
        case 7: {std::stringstream out; out << pp->getSchedDataFields(); return out.str();}
        default: return "";
    }
}

bool HomaPktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    HomaPkt_Base *pp = (HomaPkt_Base *)object; (void)pp;
    switch (field) {
        case 2: pp->setMsgId(string2uint64(value)); return true;
        case 3: pp->setPriority(string2ulong(value)); return true;
        case 4: pp->setPktType(string2long(value)); return true;
        default: return false;
    }
}

const char *HomaPktDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(inet::L3Address));
        case 1: return opp_typename(typeid(inet::L3Address));
        case 5: return opp_typename(typeid(UnschedFields));
        case 6: return opp_typename(typeid(GrantFields));
        case 7: return opp_typename(typeid(SchedDataFields));
        default: return NULL;
    };
}

void *HomaPktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    HomaPkt_Base *pp = (HomaPkt_Base *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSrcAddr()); break;
        case 1: return (void *)(&pp->getDestAddr()); break;
        case 5: return (void *)(&pp->getUnschedFields()); break;
        case 6: return (void *)(&pp->getGrantFields()); break;
        case 7: return (void *)(&pp->getSchedDataFields()); break;
        default: return NULL;
    }
}


