// This file is part of the Loobee package.
//
// (c) Andrey Savitsky <contact@qroc.pro>
//
// For the full copyright and license information, please view the LICENSE
// file that was distributed with this source code.

@testable import Loobee
import XCTest

class EnvironmentTests: XCTestCase {
    static var allTests = [
        ("testCpuId", testCpuId)
    ]

    func testCpuId() {
        XCTAssertTrue(Environment.current.cpuId.hasMmx())
    }
}
