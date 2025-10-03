#include "ina2xx_common.h"

#if INA2XX_BUS_SPI

static int ina2xx_spi_reg_read_24(const struct ina2xx_config *cfg, uint8_t reg, uint32_t *val)
{
	return -ENOTSUP;
}

static int ina2xx_spi_reg_read_16(const struct ina2xx_config *cfg, uint8_t reg, uint16_t *val)
{
	return -ENOTSUP;
}

static int ina2xx_spi_reg_read(const struct ina2xx_config *cfg, const struct ina2xx_reg *reg,
				void *buf, size_t len)
{
	return -ENOTSUP;
}

static int ina2xx_spi_reg_write(const struct ina2xx_config *cfg, uint8_t reg, uint16_t val)
{
	return -ENOTSUP;
}

const struct ina2xx_ops ina2xx_spi_ops = {
    .reg_read_24 = ina2xx_spi_reg_read_24,
    .reg_read_16 = ina2xx_spi_reg_read_16,
    .reg_read = ina2xx_spi_reg_read,
    .reg_write = ina2xx_spi_reg_write
};

#endif //INA2XX_BUS_I2C
