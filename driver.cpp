#include <iostream>
#include "json.h"
#include <vector>
class iJsonSerializable{
   

   public:
      iJsonSerializable(){};
      virtual void serialize(Json::Value& root)=0;
      virtual void deSerialize(Json::Value& root)=0;


};
class cJsonSerializer{
   public: 
   static bool serialize(iJsonSerializable * obj,std::string & output);
   static bool deSerialize(iJsonSerializable * objt, std::string & input);
   private:
   cJsonSerializer(void ){};

};

class testClassA:public iJsonSerializable{
   public:
   testClassA(void){};
   virtual ~testClassA(void){};
   virtual void serialize(Json::Value& root);
   virtual void deSerialize(Json::Value& root);
   
     
   int _testInt;
   double _testDouble;
   std::string _testString;
   bool _testBool;
   std::vector<std::string> _testStringsV;
   private:


};
class testSubClassA:public testClassA{
   public:
   testSubClassA(void){};
   virtual ~testSubClassA(void){};
   virtual void serialize(Json::Value& root);
   virtual void deSerialize(Json::Value& root);
   
   double _testSubADouble;
};
void testSubClassA::serialize(Json::Value& root){
   testClassA::serialize(root);
   root["testSubADouble"]=_testSubADouble;
}
void testSubClassA::deSerialize(Json::Value& root){
   _testSubADouble=root.get("testSubADouble",0.0).asDouble();
   this->testClassA::deSerialize(root);
}
void testClassA::serialize(Json::Value& root){
   root["testInt"]=_testInt;
   root["testDouble"]=_testDouble;
   root["testString"]=_testString;
   root["testBool"]=_testBool;
   for(std::vector<std::string>::const_iterator it = _testStringsV.begin();it!=_testStringsV.end();it++){
      root["testStringsV"].append((*it));
   }

}
void testClassA::deSerialize(Json::Value& root){
   _testInt=root.get("testInt",0).asInt();
   _testDouble=root.get("testDouble",0.0).asDouble();
   _testString=root.get("testString","").asString();
   _testBool=root.get("testBool",false).asBool();
   if(root.get("testStringsV","").isArray()){
      int size=root.get("vector","").size();
      for(int i=0;i<size;i++){
         _testStringsV.push_back(root.get("testStringsV","")[i].asString());
      }

   }

}

bool cJsonSerializer::serialize(iJsonSerializable * obj,std::string & output){
   if(obj==nullptr)
      return false;

   Json::Value jRoot;
   obj->serialize(jRoot);
  
   Json::StyledWriter writer;
   output = writer.write(jRoot);
   return true;
}

bool cJsonSerializer::deSerialize(iJsonSerializable * obj, std::string & input){
   if(obj==nullptr)
      return false;

   Json::Value jRoot;
   Json::Reader reader;
   if (!reader.parse(input,jRoot))
      return false;

   obj->deSerialize(jRoot);
   return true;
   
}

int main(){
   testSubClassA mySubTest;
   std::string inputDerived = "{ \"testInt\" : 42, \"testDouble\" : 3.14159, \"testString\" : \"foo\", \"testBool\" : true,\"testSubADouble\" : 55.55 }\n";
   cJsonSerializer::deSerialize(&mySubTest,inputDerived);
   std::cout << "raw input: " << inputDerived << std::endl;
   std::cout << "Sub: loaded value for int: " << mySubTest._testInt << std::endl;
   std::cout << "Sub: loaded value for double: " << mySubTest._testDouble << std::endl;
   std::cout << "Sub: loaded value for String: " << mySubTest._testString << std::endl;
   std::cout << "Sub: loaded value for bool: " << mySubTest._testBool<< std::endl;
   std::cout << "Sub: loaded value for SubDouble: " << mySubTest._testSubADouble<< std::endl;
   std::string outputDerived;
   cJsonSerializer::serialize(&mySubTest,outputDerived);
   std::cout << "Sub: serialized object: " << outputDerived << std::endl;

   testClassA myTest;
   std::string input = "{ \"testInt\" : 42, \"testDouble\" : 3.14159, \"testString\" : \"foo\", \"testBool\" : true }\n";
   cJsonSerializer::deSerialize(&myTest,input);
   std::cout << "raw input: " << input << std::endl;
   std::cout << "loaded value for int: " << myTest._testInt << std::endl;
   std::cout << "loaded value for double: " << myTest._testDouble << std::endl;
   std::cout << "loaded value for String: " << myTest._testString << std::endl;
   std::cout << "loaded value for bool: " << myTest._testBool<< std::endl;
   std::string output;
   cJsonSerializer::serialize(&myTest,output);
   std::cout << "serialized object: " << output << std::endl;
   return 0;
}
