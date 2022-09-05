#
# Be sure to run `pod lib lint ALiOfflinePay.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'ALiOfflinePay'
  s.version          = '0.1.0'
  s.summary          = 'A short description of ALiOfflinePay.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/lihaiyang123/ALiOfflinePay'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'lihaiyang123' => 'lihaiyang730325@qq.com' }
  s.source           = { :git => 'https://github.com/lihaiyang123/ALiOfflinePay.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '9.0'
  s.ios.vendored_libraries  = 'ALiOfflinePay/Libraries/*.{a}'
  s.source_files = 'ALiOfflinePay/Classes/**/*'
  s.xcconfig = { 'ALWAYS_EMBED_SWIFT_STANDARD_LIBRARIES' => true }
  # s.resource_bundles = {
  #   'ALiOfflinePay' => ['ALiOfflinePay/Assets/*.png']
  # }

  # s.public_header_files = 'Pod/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
  # s.dependency 'AFNetworking', '~> 2.3'
end
