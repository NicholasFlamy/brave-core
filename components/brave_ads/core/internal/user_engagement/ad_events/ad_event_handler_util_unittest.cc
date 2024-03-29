/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/user_engagement/ad_events/ad_event_handler_util.h"

#include "brave/components/brave_ads/core/internal/ad_units/ad_unittest_util.h"
#include "brave/components/brave_ads/core/internal/common/unittest/unittest_time_util.h"
#include "brave/components/brave_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "brave/components/brave_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "brave/components/brave_ads/core/mojom/brave_ads.mojom-shared.h"
#include "brave/components/brave_ads/core/public/ad_units/ad_info.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- brave_unit_tests --filter=BraveAds*

namespace brave_ads {

TEST(BraveAdsAdEventHandlerUtilTest, HasFiredAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(AdType::kNotificationAd,
                                  /*should_use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event =
      BuildAdEvent(ad, ConfirmationType::kServedImpression,
                   /*created_at=*/Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_TRUE(
      HasFiredAdEvent(ad, ad_events, ConfirmationType::kServedImpression));
}

TEST(BraveAdsAdEventHandlerUtilTest, HasNeverFiredAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(AdType::kNotificationAd,
                                  /*should_use_random_uuids=*/true);

  AdEventList ad_events;
  const AdEventInfo ad_event = BuildAdEvent(
      ad, ConfirmationType::kServedImpression, /*created_at=*/Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_FALSE(
      HasFiredAdEvent(ad, ad_events, ConfirmationType::kViewedImpression));
}

TEST(BraveAdsAdEventHandlerUtilTest, WasAdServed) {
  // Arrange
  const AdInfo ad = test::BuildAd(AdType::kNotificationAd,
                                  /*should_use_random_uuids=*/true);

  const AdEventList ad_events;

  // Act & Assert
  EXPECT_TRUE(WasAdServed(ad, ad_events,
                          mojom::InlineContentAdEventType::kServedImpression));
}

TEST(BraveAdsAdEventHandlerUtilTest, WasAdPreviouslyServed) {
  // Arrange
  const AdInfo ad = test::BuildAd(AdType::kNotificationAd,
                                  /*should_use_random_uuids=*/true);

  AdEventList ad_events;
  AdEventInfo ad_event =
      BuildAdEvent(ad, ConfirmationType::kServedImpression, Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_TRUE(WasAdServed(ad, ad_events,
                          mojom::InlineContentAdEventType::kViewedImpression));
}

TEST(BraveAdsAdEventHandlerUtilTest, WasAdNeverServed) {
  // Arrange
  const AdInfo ad = test::BuildAd(AdType::kNotificationAd,
                                  /*should_use_random_uuids=*/true);

  const AdEventList ad_events;

  // Act & Assert
  EXPECT_FALSE(WasAdServed(ad, ad_events,
                           mojom::InlineContentAdEventType::kViewedImpression));
}

TEST(BraveAdsAdEventHandlerUtilTest, ShouldDebouncePreviouslyViewedAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(AdType::kNotificationAd,
                                  /*should_use_random_uuids=*/true);

  AdEventList ad_events;
  AdEventInfo ad_event_1 =
      BuildAdEvent(ad, ConfirmationType::kServedImpression, Now());
  ad_events.push_back(ad_event_1);
  AdEventInfo ad_event_2 =
      BuildAdEvent(ad, ConfirmationType::kViewedImpression, Now());
  ad_events.push_back(ad_event_2);

  // Act & Assert
  EXPECT_TRUE(ShouldDebounceAdEvent(
      ad, ad_events, mojom::InlineContentAdEventType::kViewedImpression));
}

TEST(BraveAdsAdEventHandlerUtilTest, ShouldNotDebounceViewedAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(AdType::kNotificationAd,
                                  /*should_use_random_uuids=*/true);

  AdEventList ad_events;
  AdEventInfo ad_event =
      BuildAdEvent(ad, ConfirmationType::kServedImpression, Now());
  ad_events.push_back(ad_event);

  // Act & Assert
  EXPECT_FALSE(ShouldDebounceAdEvent(
      ad, ad_events, mojom::InlineContentAdEventType::kViewedImpression));
}

TEST(BraveAdsAdEventHandlerUtilTest, ShouldDebouncePreviouslyClickedAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(AdType::kNotificationAd,
                                  /*should_use_random_uuids=*/true);

  AdEventList ad_events;
  AdEventInfo ad_event_1 =
      BuildAdEvent(ad, ConfirmationType::kServedImpression, Now());
  ad_events.push_back(ad_event_1);
  AdEventInfo ad_event_2 =
      BuildAdEvent(ad, ConfirmationType::kViewedImpression, Now());
  ad_events.push_back(ad_event_2);
  AdEventInfo ad_event_3 = BuildAdEvent(ad, ConfirmationType::kClicked, Now());
  ad_events.push_back(ad_event_3);

  // Act & Assert
  EXPECT_TRUE(ShouldDebounceAdEvent(ad, ad_events,
                                    mojom::InlineContentAdEventType::kClicked));
}

TEST(BraveAdsAdEventHandlerUtilTest, ShouldNotDebounceClickedAdEvent) {
  // Arrange
  const AdInfo ad = test::BuildAd(AdType::kNotificationAd,
                                  /*should_use_random_uuids=*/true);

  AdEventList ad_events;
  AdEventInfo ad_event_1 =
      BuildAdEvent(ad, ConfirmationType::kServedImpression, Now());
  ad_events.push_back(ad_event_1);
  AdEventInfo ad_event_2 =
      BuildAdEvent(ad, ConfirmationType::kViewedImpression, Now());
  ad_events.push_back(ad_event_2);

  // Act & Assert
  EXPECT_FALSE(ShouldDebounceAdEvent(
      ad, ad_events, mojom::InlineContentAdEventType::kClicked));
}

}  // namespace brave_ads
