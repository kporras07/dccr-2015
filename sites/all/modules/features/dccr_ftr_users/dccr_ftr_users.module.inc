<?php
/**
 * @file
 * Custom Code for the Drupal Camp Users feature.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function dccr_ftr_users_form_user_register_form_alter(&$form, &$form_state) {
  $form['#validate'][] = 'dccr_ftr_users_form_user_register_form_validate';
}

/**
 * Implements hook_form_alter().
 */
function dccr_ftr_users_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id === 'dccr_payment_submission_form_entityform_edit_form') {
    global $user;
    $form['field_paid_users'][LANGUAGE_NONE][0]['target_id']['#default_value'] = "$user->name ($user->uid)";
    $form['field_paid_users']['#states'] = array(
      'invisible' => array(
        ':input[name="field_paying_others[und]"]' => array('checked' => FALSE),
      ),
    );
  }
}

/**
 * Implements hook_flag_flag().
 */
function dccr_ftr_users_flag_flag($flag, $entity_id, $account, $flagging) {
  dccr_ftr_users_track_user($flag, $entity_id);
}

/**
 * Implements hook_flag_unflag().
 */
function dccr_ftr_users_flag_unflag($flag, $entity_id, $account, $flagging) {
  dccr_ftr_users_track_user($flag, $entity_id);
}

/**
 * Invoke search_api_track_item_change for recently flagged user.
 */
function dccr_ftr_users_track_user($flag, $entity_id) {
  if ($flag->name === 'dccr_registration_complete') {
    search_api_track_item_change('user', array($entity_id));
  }
}

/**
 * Extra validate for user_register_form.
 */
function dccr_ftr_users_form_user_register_form_validate($form, &$form_state) {
  $name = $form_state['values']['name'];
  $pattern = '/^[a-z0-9_-]{3,16}$/';
  if (!preg_match($pattern, $name)) {
    form_set_error('name][', t('Username can contain only lowercase letters, numbers, "-" and "_"'));
  }
}
