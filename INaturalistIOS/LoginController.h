//
//  LoginController.h
//  iNaturalist
//
//  Created by Alex Shepard on 5/15/15.
//  Copyright (c) 2015 iNaturalist. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ExploreUserRealm;
@class Partner;
@class User;
@class UploadManager;

extern NSString *kUserLoggedInNotificationName;
extern NSInteger INatMinPasswordLength;

typedef void (^LoginSuccessBlock)(NSDictionary *info);
typedef void (^LoginErrorBlock)(NSError *error);

@interface LoginController : NSObject

- (void)loginWithFacebookViewController:(UIViewController *)vc
	success:(LoginSuccessBlock)success
	failure:(LoginErrorBlock)error;
- (void)loginWithGoogleUsingNavController:(UINavigationController *)nav
                                  success:(LoginSuccessBlock)success
                                  failure:(LoginErrorBlock)error;
- (void)loginWithGoogleUsingViewController:(UIViewController *)parent
                                   success:(LoginSuccessBlock)success
                                   failure:(LoginErrorBlock)error;

- (void)createAccountWithEmail:(NSString *)email
                      password:(NSString *)password
                      username:(NSString *)username
                          site:(NSInteger)siteId
                       license:(NSString *)license
                       success:(LoginSuccessBlock)successBlock
                       failure:(LoginErrorBlock)failureBlock;

- (void)loginWithUsername:(NSString *)username
                 password:(NSString *)password
                  success:(LoginSuccessBlock)successBlock
                  failure:(LoginErrorBlock)failureBlock;

- (void)logout;

- (void)loggedInUserSelectedPartner:(Partner *)partner
                         completion:(void (^)(void))completion;

// return the local me user
- (ExploreUserRealm *)meUserLocal;

// if the me user was very recently fetched and not made dirty
// (see -dirtyLocalMeUser) then return the local me user
// otherwise, if we have an outdated or dirty me user, refetch
// it from remote
- (void)meUserRemoteCompletion:(void (^)(ExploreUserRealm *me))completion;

// make the me user dirty - invalidte it's syncedAt field
// next time we fetch remote, we'll refetch regardless
// of the last time we remotely fetched it
- (void)dirtyLocalMeUser;

@property (readonly) BOOL isLoggedIn;
@property UploadManager *uploadManager;

- (void)getJWTTokenSuccess:(LoginSuccessBlock)success failure:(LoginErrorBlock)failure;
@property NSString *jwtToken;
@property NSDate *jwtTokenExpiration;
@property (readonly) NSString *anonymousJWT;

@end
