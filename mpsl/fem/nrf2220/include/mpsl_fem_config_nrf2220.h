/*
 * Copyright (c) Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/**
 * @file mpsl_fem_config_nrf2220.h
 *
 * @defgroup mpsl_fem_nrf2220 MPSL nRF2220 Front End Module Configuration
 * @ingroup  mpsl_fem
 *
 * @{
 */

#ifndef MPSL_FEM_CONFIG_NRF2220_H__
#define MPSL_FEM_CONFIG_NRF2220_H__

#include <stdint.h>
#include <stdbool.h>
#include "mpsl_fem_config_common.h"
#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Configuration structure of the nRF2220 Front End Module.
 */
typedef struct
{
    /** Output power in dBm supported by the Front End Module. */
    int8_t output_power_dbm;
    /** Gain of the Front End Module's bypass in dB. This parameter is usually negative
     *  to express attenuation. */
    int8_t bypass_gain_db;
} mpsl_fem_nrf2220_config_t;

/** @brief Configuration of the nRF2220 TWI.
 */
typedef struct
{
    /**
     * Pointer to the TWI peripheral instance to be used. If this pointer is equal @c NULL no TWI
     * communication is performed and only GPIO part of the interface is used. Otherwise, only TWIM0
     * is accepted as valid. If @p p_twim other than @c NULL or TWIM0 is provided initialization
     * of the inteface fails. Additionally, there is a limitation that no other devices on the TWI
     * bus are allowed.
     */
    NRF_TWIM_Type * p_twim;
    /** SCL pin. */
    mpsl_fem_pin_t  scl;
    /** SDA pin. */
    mpsl_fem_pin_t  sda;
    /** Clock frequency in Hz. */
    uint32_t        freq_hz;
    /** TWI slave address. */
    uint8_t         address;
} mpsl_fem_nrf2220_twi_config_t;

/** @brief Configuration parameters for the interface of the nRF2220 Front End Module.
 */
typedef struct
{
    /** nRF2220 parameters configuration. */
    mpsl_fem_nrf2220_config_t     fem_config;
    /** Chip Select pin configuration. Configuration where @ref cs_pin_config.enable is false is unsupported. */
    mpsl_fem_gpiote_pin_config_t  cs_pin_config;
    /** Mode pin configuration. Configuration where @ref md_pin_config.enable is false is unsupported. */
    mpsl_fem_gpiote_pin_config_t  md_pin_config;

    /** TWI interface configuration. */
    mpsl_fem_nrf2220_twi_config_t twi_config;

#if defined(NRF52_SERIES)
    /** Array of PPI channels which need to be provided to Front End Module to operate. */
    uint8_t                       ppi_channels[3];
#else
    /** Array of DPPI channels which need to be provided to Front End Module to operate. */
    uint8_t                       dppi_channels[2];
#endif

} mpsl_fem_nrf2220_interface_config_t;

/** @brief Configures the nRF2220 Front End Module interface.
 *
 * This function sets device interface parameters for the nRF2220.
 * It also sets the PPI and GPIOTE channels to be configured for the interface.
 *
 * @param[in] p_config Pointer to the interface parameters for the nRF2220 device.
 *
 * @retval   0             nRF2220 control interface successfully configured.
 * @retval   -NRF_EPERM    PA/LNA is not available.
 *
 */
int32_t mpsl_fem_nrf2220_interface_config_set(mpsl_fem_nrf2220_interface_config_t const * const p_config);

#ifdef __cplusplus
}
#endif

#endif // MPSL_FEM_CONFIG_NRF2220_H__

/**@} */
