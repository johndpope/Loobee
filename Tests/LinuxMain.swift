// This file is part of the Loobee package.
//
// (c) Andrey Savitsky <contact@qroc.pro>
//
// For the full copyright and license information, please view the LICENSE
// file that was distributed with this source code.

import XCTest
@testable import EnvironmentTests
@testable import ByteTests

XCTMain([
    testCase(EnvironmentTests.allTests),

    testCase(ByteTests.allTests)
])
