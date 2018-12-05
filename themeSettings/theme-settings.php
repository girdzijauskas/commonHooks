<?php

/**
 * This is not a hook and rather a
 */

function p1base_form_system_theme_settings_alter(&$form, \Drupal\Core\Form\FormStateInterface &$form_state, $form_id = NULL) {

  // Twitter timeline settings

  $form['twitter_timeline'] = array(
    '#type' => 'details',
    '#description' => t('The settings for the Twitter Timeline in the footer. Note that the classes within the timeline output are hardcoded and should be edited if this functionality is transferred to a different project.'),
    '#title' => t('Twitter Timeline'),
    '#open' => TRUE,
    '#weight' => 0,
  );

  $form['twitter_timeline']['app_settings'] = array(
    '#type' => 'details',
    '#title' => t('App Settings'),
    '#description' => t('The application keys that you can get with a developer account on Twitter. Required for the functionality of the timeline.'),
    '#open' => TRUE,
    '#weight' => 0,
  );

  $form['twitter_timeline']['timeline_settings'] = array(
    '#type' => 'details',
    '#title' => t('Timeline Settings'),
    '#description' => t('The options for the timeline itself.'),
    '#open' => TRUE,
    '#weight' => 0,
  );

  $form['twitter_timeline']['timeline_settings']['twitter_user_id'] = array(
    '#type' => 'textfield',
    '#length' => 9,
    '#title' => t('Twitter User ID'),
    '#description' => t('The Twitter user ID to display the posts from. Number that you can find within your user account settings in Twitter.'),
    '#default_value' => theme_get_setting('twitter_user_id'),
    '#weight' => 0,
  );

  $twitter_timeline_app_setttings = [
    'consumer_key',
    'consumer_secret',
    'access_token',
    'access_token_secret',
  ];

  foreach($twitter_timeline_app_setttings as $app_setting) {
    $form['twitter_timeline']['app_settings'][$app_setting] = array(
      '#type' => 'textfield',
      '#title' => t(ucwords(str_replace('_', ' ', $app_setting))),
      '#default_value' => theme_get_setting($app_setting),
    );
  }

  // Contact details settings

  $form['contact_details'] = array(
    '#type' => 'details',
    '#title' => 'Contact Details',
    '#description' => 'Contact details for the site, used in custom blocks and other templates.',
    '#open' => TRUE,
    '#weight' => -1,
  );
  $form['contact_details']['offline'] = array(
    '#type' => 'details',
    '#title' => 'Offline',
    '#description' => 'Offline contact details.',
    '#open' => TRUE,
    '#weight' => 1,
  );
  $form['contact_details']['online'] = array(
    '#type' => 'details',
    '#title' => 'Online',
    '#description' => 'Online contact details. Include the full URL with https://.',
    '#open' => TRUE,
    '#weight' => 1,
  );

  $offline_contact_settings = array(
    'office_address',
    'telephone_number',
    'fax_number',
    'email_address'
  );

  $online_contact_settings = array(
    'youtube_url',
    'facebook_url',
    'twitter_url',
  );

  foreach($offline_contact_settings as $offline_setting) {
    $form['contact_details']['offline'][$offline_setting] = array(
      '#type' => 'textfield',
      '#title' => t(ucwords(str_replace('_', ' ', $offline_setting))),
      '#default_value' => theme_get_setting($offline_setting),
    );
  }

  foreach($online_contact_settings as $online_setting) {
    $form['contact_details']['online'][$online_setting] = array(
      '#type' => 'textfield',
      '#title' => t(ucwords(str_replace('_', ' ', $online_setting))),
      '#default_value' => theme_get_setting($online_setting),
    );
  }
}