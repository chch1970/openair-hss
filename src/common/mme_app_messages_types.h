/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the Apache License, Version 2.0  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

/*! \file mme_app_messages_types.h
  \brief
  \author Sebastien ROUX, Lionel Gauthier
  \company Eurecom
  \email: lionel.gauthier@eurecom.fr
*/

#ifndef FILE_MME_APP_MESSAGES_TYPES_SEEN
#define FILE_MME_APP_MESSAGES_TYPES_SEEN

#include "nas_messages_types.h"
#include "s1ap_common.h"
#include "s10_messages_types.h"

#define MME_APP_CONNECTION_ESTABLISHMENT_CNF(mSGpTR)     (mSGpTR)->ittiMsg.mme_app_connection_establishment_cnf
#define MME_APP_INITIAL_CONTEXT_SETUP_RSP(mSGpTR)        (mSGpTR)->ittiMsg.mme_app_initial_context_setup_rsp
#define MME_APP_CREATE_DEDICATED_BEARER_REQ(mSGpTR)      (mSGpTR)->ittiMsg.mme_app_create_dedicated_bearer_req
#define MME_APP_CREATE_DEDICATED_BEARER_RSP(mSGpTR)      (mSGpTR)->ittiMsg.mme_app_create_dedicated_bearer_rsp
#define MME_APP_CREATE_DEDICATED_BEARER_REJ(mSGpTR)      (mSGpTR)->ittiMsg.mme_app_create_dedicated_bearer_rej
#define MME_APP_DELETE_DEDICATED_BEARER_REQ(mSGpTR)      (mSGpTR)->ittiMsg.mme_app_delete_dedicated_bearer_req
#define MME_APP_DELETE_DEDICATED_BEARER_RSP(mSGpTR)      (mSGpTR)->ittiMsg.mme_app_delete_dedicated_bearer_rsp

#define MME_APP_INITIAL_CONTEXT_SETUP_FAILURE(mSGpTR)    (mSGpTR)->ittiMsg.mme_app_initial_context_setup_failure
/** Necessary for TAU. */
#define MME_APP_NAS_UPDATE_LOCATION_CNF(mSGpTR)          (mSGpTR)->ittiMsg.mme_app_nas_update_location_cnf

#define MME_APP_S1AP_MME_UE_ID_NOTIFICATION(mSGpTR)      (mSGpTR)->ittiMsg.mme_app_s1ap_mme_ue_id_notification

typedef struct itti_mme_app_connection_establishment_cnf_s {
  mme_ue_s1ap_id_t        ue_id;


  ambr_t                  ue_ambr;

  // E-RAB to Be Setup List
  uint8_t                 no_of_e_rabs; // spec says max 256, actually stay with BEARERS_PER_UE
  //     >>E-RAB ID
  ebi_t                   e_rab_id[BEARERS_PER_UE];
  //     >>E-RAB Level QoS Parameters
  qci_t                   e_rab_level_qos_qci[BEARERS_PER_UE];
  //       >>>Allocation and Retention Priority
  priority_level_t        e_rab_level_qos_priority_level[BEARERS_PER_UE];
  //       >>>Pre-emption Capability
  pre_emption_capability_t    e_rab_level_qos_preemption_capability[BEARERS_PER_UE];
  //       >>>Pre-emption Vulnerability
  pre_emption_vulnerability_t e_rab_level_qos_preemption_vulnerability[BEARERS_PER_UE];
  //     >>Transport Layer Address
  bstring                 transport_layer_address[BEARERS_PER_UE];
  //     >>GTP-TEID
  teid_t                  gtp_teid[BEARERS_PER_UE];
  //     >>NAS-PDU (optional)
  bstring                 nas_pdu[BEARERS_PER_UE];
  //     >>Correlation ID TODO? later...

  // UE Security Capabilities
  uint16_t                ue_security_capabilities_encryption_algorithms;
  uint16_t                ue_security_capabilities_integrity_algorithms;

  // Security key
  uint8_t                 kenb[AUTH_KASME_SIZE];

  // Trace Activation (optional)
  // Handover Restriction List (optional)

  // UE Radio Capability (optional)
  uint8_t                 *ue_radio_capabilities;
  int                     ue_radio_cap_length;
  // todo:   bstring                 ue_radio_capability;


  // Subscriber Profile ID for RAT/Frequency priority (optional)
  // CS Fallback Indicator (optional)
  // SRVCC Operation Possible (optional)
  // CSG Membership Status (optional)
  // Registered LAI (optional)
  // GUMMEI ID (optional)
  // MME UE S1AP ID 2  (optional)
  // Management Based MDT Allowed (optional)

//  itti_nas_conn_est_cnf_t nas_conn_est_cnf;
} itti_mme_app_connection_establishment_cnf_t;

typedef struct itti_mme_app_initial_context_setup_rsp_s {
  mme_ue_s1ap_id_t        ue_id;
  uint8_t                 no_of_e_rabs;

  ebi_t                   e_rab_id[BEARERS_PER_UE];
  bstring                 transport_layer_address[BEARERS_PER_UE];
  s1u_teid_t              gtp_teid[BEARERS_PER_UE];
} itti_mme_app_initial_context_setup_rsp_t;

typedef struct itti_mme_app_create_dedicated_bearer_req_s {
  /* UE identifier */
  mme_ue_s1ap_id_t                  ue_id;
  pdn_cid_t                         cid;
  ebi_t                             linked_ebi;
  uint8_t                           num_bearers;
  /** No EBI will set yet. */
  struct fteid_set_s               *fteid_set[BEARERS_PER_UE];
  ebi_t                             ebis[BEARERS_PER_UE];
  s1u_teid_t                        saegw_s1u_teid[BEARERS_PER_UE];
  traffic_flow_template_t          *tfts[BEARERS_PER_UE];
  bearer_qos_t                      bearer_qos_vals[BEARERS_PER_UE];

  protocol_configuration_options_t *pcos[BEARERS_PER_UE];
} itti_mme_app_create_dedicated_bearer_req_t;

typedef struct itti_mme_app_create_dedicated_bearer_rsp_s {
  /* UE identifier */
  mme_ue_s1ap_id_t                  ue_id;
  ebi_t                             ebi;
} itti_mme_app_create_dedicated_bearer_rsp_t;

typedef struct itti_mme_app_create_dedicated_bearer_rej_s {
  /* UE identifier */
  mme_ue_s1ap_id_t                  ue_id;
  ebi_t                             ebi;
} itti_mme_app_create_dedicated_bearer_rej_t;

typedef struct itti_mme_app_delete_dedicated_bearer_req_s {
  /* UE identifier */
  mme_ue_s1ap_id_t                  ue_id;
  ebi_t                             ded_ebi;
  ebi_t                             def_ebi;
  pdn_cid_t                         pid;
} itti_mme_app_delete_dedicated_bearer_req_t;

typedef struct itti_mme_app_delete_dedicated_bearer_rsp_s {
  /* UE identifier */
  mme_ue_s1ap_id_t                  ue_id;
  ebi_t                             ded_ebi;
  ebi_t                             def_ebi;
  pdn_cid_t                         pid;
} itti_mme_app_delete_dedicated_bearer_rsp_t;

typedef struct itti_mme_app_s1ap_mme_ue_id_notification_s {
  enb_ue_s1ap_id_t      enb_ue_s1ap_id;
  mme_ue_s1ap_id_t      mme_ue_s1ap_id;
  sctp_assoc_id_t       sctp_assoc_id;
} itti_mme_app_s1ap_mme_ue_id_notification_t;

typedef struct itti_mme_app_initial_context_setup_failure_s {
  mme_ue_s1ap_id_t      mme_ue_s1ap_id;
} itti_mme_app_initial_context_setup_failure_t;


typedef struct itti_mme_app_nas_update_location_cnf_s {
  mme_ue_s1ap_id_t    ue_id;

  char       imsi[IMSI_BCD_DIGITS_MAX + 1]; // username
  uint8_t    imsi_length;               // username

  s6a_result_t result;

}itti_mme_app_nas_update_location_cnf_t;

#endif /* FILE_MME_APP_MESSAGES_TYPES_SEEN */
