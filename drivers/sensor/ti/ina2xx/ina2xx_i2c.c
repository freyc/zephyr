#include "ina2xx_common.h"

#if INA2XX_BUS_I2C

static bool ina2xx_i2c_bus_ready(const struct ina2xx_config *cfg)
{
    return device_is_ready(cfg->bus.bus);
}

static int ina2xx_i2c_reg_read_24(const struct ina2xx_config *cfg, uint8_t reg, uint32_t *val)
{
	uint8_t data[3];
	int ret;

	ret = i2c_burst_read_dt(bus, reg, data, sizeof(data));
	if (ret < 0) {
		return ret;
	}

	*val = sys_get_be24(data);

	return ret;
}

static int ina2xx_i2c_reg_read_16(const struct ina2xx_config *cfg, uint8_t reg, uint16_t *val)
{
	uint8_t data[2];
	int ret;

	ret = i2c_burst_read_dt(bus, reg, data, sizeof(data));
	if (ret < 0) {
		return ret;
	}

	*val = sys_get_be16(data);

	return ret;
}

static int ina2xx_i2c_reg_read(const struct ina2xx_config *cfg, const struct ina2xx_reg *reg,
				void *buf, size_t len)
{
	const size_t bytes = (reg->size + 7) / 8;

	if (len < bytes) {
		return -EINVAL;
	}

	return i2c_burst_read_dt(bus, reg->addr, buf, bytes);
}

static int ina2xx_i2c_reg_write(const struct ina2xx_config *cfg, uint8_t reg, uint16_t val)
{
	uint8_t tx_buf[3];

	tx_buf[0] = reg;
	sys_put_be16(val, &tx_buf[1]);

	return i2c_write_dt(bus, tx_buf, sizeof(tx_buf));
}

const struct ina2xx_ops ina2xx_i2c_ops = {
    .is_bus_ready = ina2xx_i2c_bus_ready,
    .reg_read_24 = ina2xx_i2c_reg_read_24,
    .reg_read_16 = ina2xx_i2c_reg_read_16,
    .reg_read = ina2xx_i2c_reg_read,
    .reg_write = ina2xx_i2c_reg_write
};

#endif //INA2XX_BUS_I2C
