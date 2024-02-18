# SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: CC0-1.0

import logging
import os

import pytest
from pytest_embedded_idf.dut import IdfDut


@pytest.mark.supported_targets
@pytest.mark.generic
def test_esp_s3_eye_lvgl(dut: IdfDut) -> None:
    # check and log bin size
    binary_file = os.path.join(dut.app.binary_path, 'esp_s3_eye_lvgl.bin')
    bin_size = os.path.getsize(binary_file)
    logging.info('esp_s3_eye_lvgl_bin_size : {}KB'.format(bin_size // 1024))
