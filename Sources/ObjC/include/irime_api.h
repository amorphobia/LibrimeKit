#import "irime_entity.h"
#import <Foundation/Foundation.h>

typedef uintptr_t RimeSessionId;
/**
 对 rime_api.h 的 notification 回调函数封装
 */
@protocol IRimeNotificationDelegate

// message_type="deploy", message_value="start"
- (void)onDeployStart;

//  message_type="deploy", message_value="success"
- (void)onDeploySuccess;

// message_type="deploy", message_value="failure"
- (void)onDeployFailure;

// on changing mode
- (void)onChangeMode:(NSString *)mode;

// on loading schema
- (void)onLoadingSchema:(NSString *)schema;

@end

/**
 RIME输入法引擎
 使用OC对rime_api的c接口进行封装, 方便swift调用
 */
@interface IRimeAPI : NSObject

- (void)setNotificationDelegate:(id<IRimeNotificationDelegate>)delegate;

// MARK: start and shutdown
- (void)setup:(IRimeTraits *)traits;
- (void)initialize:(IRimeTraits *)traits;
- (void)finalize;

- (void)startMaintenance:(BOOL)fullCheck;

- (void)syncUserData;

// Session management
- (RimeSessionId)createSession;
- (BOOL)findSession:(RimeSessionId)session;
- (void)cleanAllSession;

// MARK: input and output
- (BOOL)processKey:(NSString *)keyCode andSession:(RimeSessionId)session;
- (BOOL)processKeyCode:(int)code modifier:(int)modifier andSession:(RimeSessionId)session;
- (NSArray<IRimeCandidate *> *)getCandidateList:(RimeSessionId)session;
// MAKR: index从1开始
- (NSArray<IRimeCandidate *> *)getCandidateWithIndex:(int)index
                                            andCount:(int)limit
                                          andSession:(RimeSessionId)session;
// MAKR: index从1开始
- (BOOL)selectCandidate:(RimeSessionId)session andIndex:(int)index;
- (BOOL)deleteCandidate:(RimeSessionId)session andIndex:(int)index;

- (NSString *)getInput:(RimeSessionId)session;
- (NSString *)getCommit:(RimeSessionId)session;
- (BOOL)commitComposition:(RimeSessionId)session;
- (void)cleanComposition:(RimeSessionId)session;
- (IRimeStatus *)getStatus:(RimeSessionId)session;
- (IRimeContext *)getContext:(RimeSessionId)session;

// MARK: schema
- (NSArray<IRimeSchema *> *)schemaList;
- (IRimeSchema *)currentSchema:(RimeSessionId)session;
- (BOOL)selectSchema:(RimeSessionId)session andSchameId:(NSString *)schemaId;

// MARK: Configuration
- (BOOL)getOption:(RimeSessionId)session andOption:(NSString *)option;
- (BOOL)setOption:(RimeSessionId)session
        andOption:(NSString *)option
         andValue:(BOOL)value;
// open <schema_id>.schema.yaml
- (IRimeConfig *)openSchema:(NSString *)schemaId;
// open <config_id>.yaml
- (IRimeConfig *)openConfig:(NSString *)configId;

// MARK: Debug
- (void)simulateKeySequence:(NSString *)keys andSession:(RimeSessionId)session;
@end
