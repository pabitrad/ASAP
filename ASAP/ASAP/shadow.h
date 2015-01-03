#pragma once

// VSS includes
#include <vss.h>
#include <vswriter.h>
#include <vsbackup.h>
#include <vsmgmt.h>

// VDS includes
#include <vds.h>

// Our includes
#include "tracing.h"
#include "util.h"
#include "writer.h"
#include "VssHelper.h"

// Software provider GUID  {8BE135FF-6D2A-42A5-BF30-609A10494335}
const GUID VSS_SWPRV_ProviderId =
{ 0x8be135ff, 0x6d2a, 0x42a5, { 0xbf, 0x30, 0x60, 0x9a, 0x10, 0x49, 0x43, 0x35 } };
