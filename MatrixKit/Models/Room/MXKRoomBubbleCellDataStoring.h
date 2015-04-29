/*
 Copyright 2015 OpenMarket Ltd

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#import <Foundation/Foundation.h>
#import <MatrixSDK/MatrixSDK.h>

#import "MXKRoomDataSource.h"

#import "MXEvent+MatrixKit.h"

@class MXKRoomDataSource;
/**
 `MXKRoomBubbleCellDataStoring` defines a protocol a class must conform in order to store MXKRoomBubble cell data
 managed by `MXKRoomDataSource`.
 */
@protocol MXKRoomBubbleCellDataStoring <NSObject>

#pragma mark - Data displayed by a room bubble cell

/**
 The sender Id
 */
@property (nonatomic) NSString *senderId;

/**
 The room id
 */
@property (nonatomic) NSString *roomId;

/**
 The sender display name composed when event occured
 */
@property (nonatomic) NSString *senderDisplayName;

/**
 The sender avatar url retrieved when event occured
 */
@property (nonatomic) NSString *senderAvatarUrl;

/**
 YES if the previous bubble sender is the same as the previous stored bubble.
 */
@property (nonatomic) BOOL isSameSenderAsPreviousBubble;

/**
 The list of events (`MXEvent` instances) handled by this bubble.
 */
@property (nonatomic, readonly) NSArray *events;

/**
 The bubble date
 */
@property (nonatomic) NSDate *date;

/**
 YES when the bubble is composed by incoming event(s).
 */
@property (nonatomic) BOOL isIncoming;

/**
 YES when the bubble correspond to an attachment (image, audio, video, location...).
 */
@property (nonatomic) BOOL isAttachment;

/**
 The body of the message with sets of attributes, or kind of content description in case of attachment (e.g. "image attachment")
 */
@property (nonatomic) NSAttributedString *attributedTextMessage;

/**
 YES if the sender name appears at the beginning of the message text
 */
@property (nonatomic) BOOL startsWithSenderName;

/**
 YES if the sender is currently typing in the current room
 */
@property (nonatomic) BOOL isTyping;

/**
 Show the date time label in rendered bubble cell (NO by default)
 */
@property (nonatomic) BOOL showBubbleDateTime;


#pragma mark - Public methods
/**
 Create a new `MXKRoomBubbleCellDataStoring` object for a new bubble cell.
 
 @param event the event to be displayed in the cell.
 @param roomState the room state when the event occured.
 @param roomDataSource the `MXKRoomDataSource` object that will use this instance.
 @return the newly created instance.
 */
- (instancetype)initWithEvent:(MXEvent*)event andRoomState:(MXRoomState*)roomState andRoomDataSource:(MXKRoomDataSource*)roomDataSource;

/**
Update the event because its mxkState changed or it is has been redacted.
 
 @param eventId the id of the event to change.
 @param the new event data
 @return the number of events hosting by the object after the update.
 */
- (NSUInteger)updateEvent:(NSString*)eventId withEvent:(MXEvent*)event;

/**
 Remove the event from the `MXKRoomBubbleCellDataStoring` object.

 @param eventId the id of the event to remove.
 @return the number of events still hosting by the object after the removal
 */
- (NSUInteger)removeEvent:(NSString*)eventId;

/**
 Check if the receiver has the same sender as another bubble.
 
 @param bubbleCellData an object conforms to `MXKRoomBubbleCellDataStoring` protocol.
 @return YES if the receiver has the same sender as the provided bubble
 */
- (BOOL)hasSameSenderAsBubbleCellData:(id<MXKRoomBubbleCellDataStoring>)bubbleCellData;

@optional
/**
 Attempt to add a new event to the bubble.
 
 @param event the event to be displayed in the cell.
 @param roomState the room state when the event occured.
 @return YES if the model accepts that the event can concatenated to events already in the bubble.
 */
- (BOOL)addEvent:(MXEvent*)event andRoomState:(MXRoomState*)roomState;

/**
 The receiver appends to its content the provided bubble cell data, if both have the same sender.
 
 @param bubbleCellData an object conforms to `MXKRoomBubbleCellDataStoring` protocol.
 @return YES if the provided cell data has been merged into receiver.
 */
- (BOOL)mergeWithBubbleCellData:(id<MXKRoomBubbleCellDataStoring>)bubbleCellData;

@end