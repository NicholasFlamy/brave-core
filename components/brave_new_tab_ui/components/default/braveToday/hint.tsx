// Copyright (c) 2020 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import * as React from 'react'
import styled, { keyframes } from 'brave-ui/theme'
import { CaratStrongDownIcon } from 'brave-ui/components/icons'

const bounceAnimation = keyframes`
  50% {
    transform: translateY(-6px);
  }
`

const Hint = styled('div')`
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 12px;
  text-align: center;
  font-size: 15px;
  color: white;
  > p {
    margin: 0;
  }
`

const Graphic = styled('div')`
  width: 16px;
  height: 16px;
  animation-name: ${bounceAnimation};
  animation-duration: 3200ms;
  animation-timing-function: cubic-bezier(0.445, 0.05, 0.55, 0.95);
  animation-iteration-count: infinite;
  animation-play-state: running;
`

export default function BraveTodayHint () {
  return (
    <Hint>
      <p>Scroll for Brave Today</p>
      <Graphic>
        <CaratStrongDownIcon />
      </Graphic>
    </Hint>
  )
}
