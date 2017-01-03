//
//  MRBServer.h
//  Merhaba
//
//  Created by Abdullah Selek on 02/01/2017.
//
//  MIT License
//
//  Copyright (c) 2017 Abdullah Selek
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.

#import <Foundation/Foundation.h>

extern NSString * const MRBDefaultProtocol;

@class MRBServer;

/**
  * Protocol for MRBServer
 */
@protocol MRBServerDelegate <NSObject>

/**
  * Both sides of the connection are ready to go
  *
  * @param server MRBServer
 */
- (void)serverRemoteConnectionComplete:(MRBServer *)server;

/**
  * server is finished stopping
  *
  * @param server MRBServer
 */
- (void)serverStopped:(MRBServer *)server;

/**
  * Server could not start
  *
  * @param server MRBServer
  * @param errorDict NSDictionary
 */
- (void)server:(MRBServer *)server didNotStart:(NSDictionary *)errorDict;

/**
  * Gets data from the remote side of the server
  *
  * @param server MRBServer
  * @param data NSData
 */
- (void)server:(MRBServer *)server didAcceptData:(NSData *)data;

/**
  * connection to the remote side is lost
  *
  * @param server MRBServer
  * @param errorDict NSDictionary
 */
- (void)server:(MRBServer *)server lostConnection:(NSDictionary *)errorDict;

/**
  * A new service comes on line
  *
  * @param service NSNetService
  * @param more BOOL
 */
- (void)serviceAdded:(NSNetService *)service moreComing:(BOOL)more;

/**
  * A service went off line
  *
  * @param service NSNetService
  * @param more BOOL
 */
- (void)serviceRemoved:(NSNetService *)service moreComing:(BOOL)more;

@end

typedef NS_ENUM(NSInteger, MRBServerErrorCode) {
    MRBServerCouldNotBindToIPv4Address,
    MRBServerCouldNotBindToIPv6Address,
    MRBServerNoSocketsAvailable,
    MRBServerNoSpaceOnOutputStream,
    MRBServerOutputStreamReachedCapacity
};

@interface MRBServer : NSObject

/**
  * the bonjour domain
 */
@property (nonatomic) NSString *domain;
/**
  * the bonjour protocol
 */
@property (nonatomic) NSString *protocol;
/**
  * the bonjour name
 */
@property (nonatomic) NSString *name;
/**
  * the port, reterieved from the OS
 */
@property (nonatomic) uint16_t port;
/**
  * the size you expect to be sending
 */
@property (nonatomic) uint8_t payloadSize;
/**
  * when there is space in the output stream this is YES
 */
@property (nonatomic) BOOL outputStreamHasSpace;

/**
  * Uses protocol as the bonjour protocol and TCP as the networking layer
  *
  * @param protocol NSString
 */
- (id)initWithProtocol:(NSString *)protocol;

/**
  * Initialize with name, protocol and name
  *
  * @param domain NSString
  * @param protocol NSString
  * @param name NSString
 */
- (id)initWithDomainName:(NSString *)domain
                protocol:(NSString *)protocol
                    name:(NSString *)name;

@end
