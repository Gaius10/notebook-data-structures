#pragma once

typedef enum {
  /// Success
  LL_STATUS_OK,
  /// Malloc failed
  LL_STATUS_MEM,
  /// Empty list
  LL_STATUS_EMPTY,
} ll_status_t;
