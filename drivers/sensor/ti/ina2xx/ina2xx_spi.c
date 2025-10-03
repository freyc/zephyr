#include "ina2xx_common.h"

#include <sys/byteorder.h>

#if INA2XX_BUS_SPI

static int ina2xx_spi_reg_read_24(const struct ina2xx_config *cfg, uint8_t reg, uint32_t *val)
{
	uint8_t cmd_buf[1] = {reg << 2 | 0x01};
	uint8_t rx_buffer[3];
	
	const struct spi_buf tx_buf = {
		.buf = cmd_buf,
		.len = sizeof(cmd_buf)
	};
	const struct spi_buf_set tx = {
		.buffers = &tx_buf,
		.count = 1
	};

	const struct spi_buf rx_buf[] = {
		{
			.buf = NULL,
			.len = sizeof(cmd_buf)
		},
		{
			.buf = rx_buffer,
			.len = sizeof(rx_buffer)
		},
	};
	const struct spi_buf_set rx = {
		.buffers = &rx_buf,
		.count = 2
	};

	int result = spi_transceive_dt(&bus->spi, &tx, &rx);
	if(result == 0)
	{
		*val = sys_get_be24(rx_buffer);
	}
	return result;
}

static int ina2xx_spi_reg_read_16(const struct ina2xx_config *cfg, uint8_t reg, uint16_t *val)
{
	uint8_t cmd_buf[1] = {reg << 2 | 0x01};
	uint8_t rx_buffer[2];
	
	const struct spi_buf tx_buf = {
		.buf = cmd_buf,
		.len = sizeof(cmd_buf)
	};
	const struct spi_buf_set tx = {
		.buffers = &tx_buf,
		.count = 1
	};

	const struct spi_buf rx_buf[] = {
		{
			.buf = NULL,
			.len = sizeof(cmd_buf)
		},
		{
			.buf = rx_buffer,
			.len = sizeof(rx_buffer)
		},
	};
	const struct spi_buf_set rx = {
		.buffers = &rx_buf,
		.count = 2
	};

	int result = spi_transceive_dt(&bus->spi, &tx, &rx);
	if(result == 0)
	{
		*val = sys_get_be16(rx_buffer);
	}
	return result;
}

static int ina2xx_spi_reg_read(const struct ina2xx_config *cfg, const struct ina2xx_reg *reg,
				void *buf, size_t len)
{
	const size_t bytes = (reg->size + 7) / 8;

	if (len < bytes) {
		return -EINVAL;
	}

	uint8_t cmd_buf[1] = {reg << 2 | 0x01};

	const struct spi_buf tx_buf = {
		.buf = cmd_buf,
		.len = sizeof(cmd_buf)
	};
	const struct spi_buf_set tx = {
		.buffers = &tx_buf,
		.count = 1
	};

	const struct spi_buf rx_buf[] = {
		{
			.buf = NULL,
			.len = sizeof(cmd_buf)
		},
		{
			.buf = buf,
			.len = len
		},
	};
	const struct spi_buf_set rx = {
		.buffers = &rx_buf,
		.count = 2
	};

	return spi_transceive_dt(&bus->spi, &tx, &rx);
}

static int ina2xx_spi_reg_write(const struct ina2xx_config *cfg, uint8_t reg, uint16_t val)
{
	uint8_t tx_buf[3];

	tx_buf[0] = reg << 2;
	sys_put_be16(val, &tx_buf[1]);

	return spi_write_dt(cfg->bus->spi, tx_buf, sizeof(tx_buf));
}

const struct ina2xx_ops ina2xx_spi_ops = {
    .reg_read_24 = ina2xx_spi_reg_read_24,
    .reg_read_16 = ina2xx_spi_reg_read_16,
    .reg_read = ina2xx_spi_reg_read,
    .reg_write = ina2xx_spi_reg_write
};

#endif //INA2XX_BUS_I2C
