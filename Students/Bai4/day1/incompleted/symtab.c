/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object* obj);
void freeScope(Scope* scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab* symtab;
Type* intType;
Type* charType;

/******************* Type utilities ******************************/

Type* makeIntType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type* makeCharType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type* makeArrayType(int arraySize, Type* elementType) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type* duplicateType(Type* type) {
  // TODO
	 Type* type2 = (Type*) malloc(sizeof(Type));
 	type2->typeClass= type->typeClass;
 	type2->arraySize=type->arraySize;
 	type2->elementType=type->elementType;
 	return type2;

}

int compareType(Type* type1, Type* type2) {
  // TODO

}

void freeType(Type* type) {
  // TODO
}

/******************* Constant utility ******************************/

ConstantValue* makeIntConstant(int i) {
  // TODO
	ConstantValue *constantValue=(ConstantValue*)malloc(sizeof(ConstantValue));
	constantValue->typeClass=TP_INT;
	constantValue->intValue=i;
	return constantValue;

}

ConstantValue* makeCharConstant(char ch) {
  // TODO
	ConstantValue *constantValue=(ConstantValue*)malloc(sizeof(ConstantValue));
	constantValue->typeClass=TP_CHAR;
	constantValue->charValue=i;
	return constantValue;
}

ConstantValue* duplicateConstantValue(ConstantValue* v) {
  // TODO
	ConstantValue *constantValue2=(ConstantValue*)malloc(sizeof(ConstantValue));

	constantValue2->typeClass=constantValue->typeClass;
	if(constantValue->typeClass==TP_CHAR){
	constantValue2->charValue=constantValue->charValue;	
	}
	else{
		constantValue2->intValue=constantValue->intValue;
	}
	return constantValue2;
}

/******************* Object utilities ******************************/

Scope* createScope(Object* owner, Scope* outer) {
  Scope* scope = (Scope*) malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object* createProgramObject(char *programName) {
  Object* program = (Object*) malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes*) malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program,NULL);
  symtab->program = program;

  return program;
}

Object* createConstantObject(char *name) {
  // TODO
	Object * object=(Object *)malloc(sizeof(Object));
	strcpy(object->name,name);
	object->kind=OBJ_CONSTANT;
	object->constAttrs=(ConstantAttributes *)malloc(sizeof(ConstantAttributes));
	//object->constAttrs->value=(ConstantValue *)malloc(sizeof(ConstantValue));
	return object;
}

Object* createTypeObject(char *name) {
  // TODO
	Object * object=(Object *)malloc(sizeof(Object));
	strcpy(object->name,name);
	object->kind=OBJ_TYPE;
	object->typeAttrs=(TypeAttributes *)malloc(sizeof(TypeAttributes));
	return object;
}

Object* createVariableObject(char *name) {
  // TODO
	Object * object=(Object *)malloc(sizeof(Object));
	strcpy(object->name,name);
	object->kind=OBJ_VARIABLE;
	object->varAttrs=(VariableAttributes *)malloc(sizeof(VariableAttributes));
	return object;
}

Object* createFunctionObject(char *name) {
  // TODO
	Object * object=(Object *)malloc(sizeof(Object));
	strcpy(object->name,name);
	object->kind=OBJ_FUNCTION;
	object->funcAttrs=(FunctionAttributes *)malloc(sizeof(FunctionAttributes));
	return object;
}

Object* createProcedureObject(char *name) {
  // TODO
	Object * object=(Object *)malloc(sizeof(Object));
	strcpy(object->name,name);
	object->kind=OBJ_PROCEDURE;
	object->procAttrs=(ProcedureAttributes *)malloc(sizeof(ProcedureAttributes));
	return object;

}

Object* createParameterObject(char *name, enum ParamKind kind, Object* owner) {
  // TODO
	Object * object=(Object *)malloc(sizeof(Object));
	strcpy(object->name,name);
	object->kind=OBJ_PARAMETER;
	object->paramAttrs=(ParameterAttributes *)malloc(sizeof(ParameterAttributes));
	return object;
}

void freeObject(Object* obj) {
  // TODO
}

void freeScope(Scope* scope) {
  // TODO
}

void freeObjectList(ObjectNode *objList) {
  // TODO
}

void freeReferenceList(ObjectNode *objList) {
  // TODO
}

void addObject(ObjectNode **objList, Object* obj) {
  ObjectNode* node = (ObjectNode*) malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL) 
    *objList = node;
  else {
    ObjectNode *n = *objList;
    while (n->next != NULL) 
      n = n->next;
    n->next = node;
  }
}

Object* findObject(ObjectNode *objList, char *name) {
  // TODO
}

/******************* others ******************************/

void initSymTab(void) {
  Object* obj;
  Object* param;

  symtab = (SymTab*) malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;
  
  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void) {
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope* scope) {
  symtab->currentScope = scope;
}

void exitBlock(void) {
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object* obj) {
  if (obj->kind == OBJ_PARAMETER) {
    Object* owner = symtab->currentScope->owner;
    switch (owner->kind) {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }
 
  addObject(&(symtab->currentScope->objList), obj);
}


