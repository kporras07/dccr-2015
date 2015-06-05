Feature: homepage initial setup
  As an anonymous user, I can go to / see the homepage.

  @homepage
  Scenario: Find 'The country greatest web event' text in homepage.
     Given I am on homepage
      Then I should see "The country greatest web event"
