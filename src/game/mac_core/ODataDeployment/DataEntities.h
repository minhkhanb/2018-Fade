/**
*
*Copyright 2010 Microsoft Corp
*
*Licensed under the Apache License, Version 2.0 (the "License");
*you may not use this file except in compliance with the License.
*You may obtain a copy of the License at
*
*http://www.apache.org/licenses/LICENSE-2.0
*
*Unless required by applicable law or agreed to in writing, software
*distributed under the License is distributed on an "AS IS" BASIS,
*WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*See the License for the specific language governing permissions and
*limitations under the License.
*/
/**
* This code was generated by the tool 'odatagen'.
* Runtime Version:1.0
*
* Changes to this file may cause incorrect behavior and will be lost if
* the code is regenerated.
*/
/**
* Defines default Data Service URL for this proxy class
*/
#define DEFAULT_SERVICE_URL @""


#define DataServiceVersion @"1.0"

#import "ODataObject.h"
#import "ObjectContext.h"
#import "DataServiceQuery.h"
#import "ODataGUID.h"
#import "ODataBool.h"
#import  "mProperties.h"


/**
 * @interface:Category
 * @Type:EntityType
 
 * @key:CategoryID* 
 */
@interface UserData : ODataObject
{
	
	/**
	* @Type:EntityProperty
	* NotNullable
	* @EdmType:Edm.String
	* @MaxLength:50
	* @FixedLength:true
	*/
	NSString *m_UserName;
	
	/**
	* @Type:EntityProperty
	* NotNullable
	* @EdmType:Edm.String
	* @MaxLength:50
	* @FixedLength:true
	*/
	NSString *m_UserID;
	
	
	/**
	* @Type:EntityProperty
	* NotNullable
	* @EdmType:Edm.String
	* @MaxLength:50
	* @FixedLength:true
	*/
	NSString *m_FacebookID;
		
	/**
	* @Type:EntityProperty
	* NotNullable
	* @EdmType:Edm.String
	* @MaxLength:50
	* @FixedLength:true
	*/
	NSString *m_GameCenterID;
	
	
	/**
	* @Type:EntityProperty
	* NotNullable
	* @EdmType:Edm.String
	* @MaxLength:50
	* @FixedLength:true
	*/
	NSString *m_SecrectKeyID;
	
	/**
	* @Type:EntityProperty
	* @EdmType:Edm.Binary
	* @MaxLength:100000
	* @FixedLength:true
	*/
	NSData *m_Record;
	
	
	
}

@property ( nonatomic , retain , getter=getUserName , setter=setUserName: )NSString *m_UserName;
@property ( nonatomic , retain , getter=getUserID , setter=setUserID: ) NSString *m_UserID;
@property ( nonatomic , retain , getter=getFacebookID , setter=setFacebookID: ) NSString *m_FacebookID;
@property ( nonatomic , retain , getter=getGameCenterID , setter=setGameCenterID: )NSString *m_GameCenterID;
@property ( nonatomic , retain , getter=getSecretKeyID , setter=setSecretKeyID: )NSString *m_SecrectKeyID;
@property ( nonatomic , retain , getter=getRecord , setter=setRecord: )NSData *m_Record;

+ (id) CreateEntityWithGameCenterID:(NSString *)GameCenterID categoryname:(NSString *)GameCenterName;
- (id) init;
- (id) initWithUri:(NSString*)anUri;
@end

