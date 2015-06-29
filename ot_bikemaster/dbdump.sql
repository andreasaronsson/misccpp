--
-- PostgreSQL database dump
--

SET client_encoding = 'LATIN1';
SET check_function_bodies = false;

SET SESSION AUTHORIZATION 'postgres';

SET search_path = public, pg_catalog;

--
-- TOC entry 28 (OID 8218450)
-- Name: plpgsql_call_handler(); Type: FUNC PROCEDURAL LANGUAGE; Schema: public; Owner: postgres
--

CREATE FUNCTION plpgsql_call_handler() RETURNS language_handler
    AS '$libdir/plpgsql', 'plpgsql_call_handler'
    LANGUAGE c;


SET SESSION AUTHORIZATION DEFAULT;

--
-- TOC entry 27 (OID 8218451)
-- Name: plpgsql; Type: PROCEDURAL LANGUAGE; Schema: public; Owner: 
--

CREATE TRUSTED PROCEDURAL LANGUAGE plpgsql HANDLER plpgsql_call_handler;


SET SESSION AUTHORIZATION 'postgres';

--
-- TOC entry 4 (OID 2200)
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


SET SESSION AUTHORIZATION 'ot04-5';

--
-- TOC entry 5 (OID 80432310)
-- Name: frame; Type: TABLE; Schema: public; Owner: ot04-5
--

CREATE TABLE frame (
    id serial NOT NULL,
    name character varying(50),
    model character varying(50),
    serialnumber character varying(50),
    sensorpos character varying(5),
    "type" character varying(50),
    description text,
    CONSTRAINT frame_sensorpos CHECK (((((sensorpos)::text = 'front'::text) OR ((sensorpos)::text = 'back'::text)) OR ((sensorpos)::text = 'none'::text)))
);


--
-- TOC entry 6 (OID 80432321)
-- Name: bike; Type: TABLE; Schema: public; Owner: ot04-5
--

CREATE TABLE bike (
    id serial NOT NULL,
    frame integer,
    backwheel integer,
    frontwheel integer,
    bikegearing integer,
    wheelgearing integer,
    fronttire integer,
    backtire integer,
    computer integer,
    assemblydate date
);


--
-- TOC entry 7 (OID 80432328)
-- Name: wheel; Type: TABLE; Schema: public; Owner: ot04-5
--

CREATE TABLE wheel (
    id serial NOT NULL,
    name character varying(50),
    brand character varying(50),
    model character varying(50),
    circumference real,
    "type" character varying(5),
    description text,
    CONSTRAINT wheel_circumference CHECK (((circumference >= (0.00)::double precision) OR (circumference <= (9999.99)::double precision))),
    CONSTRAINT wheel_type CHECK (((("type")::text = 'front'::text) OR (("type")::text = 'back'::text)))
);


--
-- TOC entry 8 (OID 80432340)
-- Name: gearing; Type: TABLE; Schema: public; Owner: ot04-5
--

CREATE TABLE gearing (
    id serial NOT NULL,
    noofcogwheels smallint,
    noofteeth smallint[],
    "type" character varying(5),
    name character varying(50),
    CONSTRAINT gearing_type CHECK (((("type")::text = 'bike'::text) OR (("type")::text = 'wheel'::text)))
);


--
-- TOC entry 9 (OID 80432351)
-- Name: computer; Type: TABLE; Schema: public; Owner: ot04-5
--

CREATE TABLE computer (
    id serial NOT NULL,
    brand character varying(50),
    model character varying(50),
    serialnumber character varying(50),
    settings real,
    tripdistance boolean,
    triptime boolean,
    odometer boolean,
    averagecadence boolean,
    altimeter boolean,
    maxspeed boolean,
    averagespeed boolean,
    maxodo real,
    bike integer,
    name character varying(50),
    CONSTRAINT computer_maxodo CHECK (((maxodo >= (0)::double precision) OR (maxodo <= (9999.99)::double precision))),
    CONSTRAINT computer_settings CHECK (((settings >= (0)::double precision) OR (settings <= (9999.99)::double precision)))
);


--
-- TOC entry 10 (OID 80432360)
-- Name: checkpoint; Type: TABLE; Schema: public; Owner: ot04-5
--

CREATE TABLE "checkpoint" (
    id serial NOT NULL,
    "location" text,
    distance real,
    altitude real,
    trail integer NOT NULL
);


--
-- TOC entry 11 (OID 80432368)
-- Name: ride; Type: TABLE; Schema: public; Owner: ot04-5
--

CREATE TABLE ride (
    ridedate date NOT NULL,
    starttime time without time zone NOT NULL,
    amountofsleep time without time zone,
    trainingtime time without time zone,
    elapsedtime time without time zone,
    odobefore real,
    odoafter real,
    averagespeed real,
    maxspeed real,
    tempdata boolean,
    maxtemp real,
    mintemp real,
    rating character varying(50),
    "type" character varying(50),
    bike integer NOT NULL,
    trail integer NOT NULL
);


--
-- TOC entry 12 (OID 80432374)
-- Name: trail; Type: TABLE; Schema: public; Owner: ot04-5
--

CREATE TABLE trail (
    id serial NOT NULL,
    name character varying(50),
    stationary boolean,
    usefrontwheel boolean,
    usebackwheel boolean,
    mapreference text,
    distance real,
    maxaltitude real,
    minaltitude real,
    accumaltitude real,
    roadcondition character varying(50),
    skilllevel character varying(50),
    description text
);


--
-- TOC entry 13 (OID 80432384)
-- Name: tire; Type: TABLE; Schema: public; Owner: ot04-5
--

CREATE TABLE tire (
    id serial NOT NULL,
    brand character varying(50),
    model character varying(50),
    wheel integer,
    name character varying(50)
);


--
-- TOC entry 14 (OID 80432391)
-- Name: preferences; Type: TABLE; Schema: public; Owner: ot04-5
--

CREATE TABLE preferences (
    id serial NOT NULL,
    distance character varying(5),
    height character varying(6),
    speed character varying(4),
    "temp" character varying(1),
    weight character varying(6),
    width character varying(4),
    CONSTRAINT preferences_distance CHECK ((((distance)::text = 'km'::text) OR ((distance)::text = 'miles'::text))),
    CONSTRAINT preferences_height CHECK ((((height)::text = 'meters'::text) OR ((height)::text = 'feet'::text))),
    CONSTRAINT preferences_speed CHECK ((((speed)::text = 'km/h'::text) OR ((speed)::text = 'mph'::text))),
    CONSTRAINT preferences_temp CHECK (((("temp")::text = 'C'::text) OR (("temp")::text = 'F'::text))),
    CONSTRAINT preferences_weight CHECK ((((weight)::text = 'kilo'::text) OR ((weight)::text = 'pounds'::text))),
    CONSTRAINT preferences_width CHECK ((((width)::text = 'cm'::text) OR ((width)::text = 'inch'::text)))
);


--
-- TOC entry 15 (OID 80432404)
-- Name: dateformat; Type: TABLE; Schema: public; Owner: ot04-5
--

CREATE TABLE dateformat (
    id serial NOT NULL,
    dateorder character varying(3),
    monthformat character varying(6),
    weekstarts character varying(8),
    dayleadingzeroes boolean,
    century smallint,
    CONSTRAINT dateformat_century CHECK (((century = 2) OR (century = 4))),
    CONSTRAINT dateformat_dateorder CHECK (((((dateorder)::text = 'MDY'::text) OR ((dateorder)::text = 'DMY'::text)) OR ((dateorder)::text = 'YMD'::text))),
    CONSTRAINT dateformat_monthformat CHECK (((((monthformat)::text = 'full'::text) OR ((monthformat)::text = 'short'::text)) OR ((monthformat)::text = 'number'::text))),
    CONSTRAINT dateformat_weekstarts CHECK ((((weekstarts)::text = 'monday'::text) OR ((weekstarts)::text = 'saturday'::text)))
);


--
-- TOC entry 16 (OID 80432317)
-- Name: frame_pkey; Type: CONSTRAINT; Schema: public; Owner: ot04-5
--

ALTER TABLE ONLY frame
    ADD CONSTRAINT frame_pkey PRIMARY KEY (id);


--
-- TOC entry 17 (OID 80432324)
-- Name: bike_pkey; Type: CONSTRAINT; Schema: public; Owner: ot04-5
--

ALTER TABLE ONLY bike
    ADD CONSTRAINT bike_pkey PRIMARY KEY (id);


--
-- TOC entry 18 (OID 80432336)
-- Name: wheel_pkey; Type: CONSTRAINT; Schema: public; Owner: ot04-5
--

ALTER TABLE ONLY wheel
    ADD CONSTRAINT wheel_pkey PRIMARY KEY (id);


--
-- TOC entry 19 (OID 80432347)
-- Name: gearing_pkey; Type: CONSTRAINT; Schema: public; Owner: ot04-5
--

ALTER TABLE ONLY gearing
    ADD CONSTRAINT gearing_pkey PRIMARY KEY (id);


--
-- TOC entry 20 (OID 80432356)
-- Name: computer_pkey; Type: CONSTRAINT; Schema: public; Owner: ot04-5
--

ALTER TABLE ONLY computer
    ADD CONSTRAINT computer_pkey PRIMARY KEY (id);


--
-- TOC entry 21 (OID 80432366)
-- Name: checkpoint_pkey; Type: CONSTRAINT; Schema: public; Owner: ot04-5
--

ALTER TABLE ONLY "checkpoint"
    ADD CONSTRAINT checkpoint_pkey PRIMARY KEY (id);


--
-- TOC entry 22 (OID 80432370)
-- Name: ride_pkey; Type: CONSTRAINT; Schema: public; Owner: ot04-5
--

ALTER TABLE ONLY ride
    ADD CONSTRAINT ride_pkey PRIMARY KEY (ridedate, starttime);


--
-- TOC entry 23 (OID 80432380)
-- Name: trail_pkey; Type: CONSTRAINT; Schema: public; Owner: ot04-5
--

ALTER TABLE ONLY trail
    ADD CONSTRAINT trail_pkey PRIMARY KEY (id);


--
-- TOC entry 24 (OID 80432387)
-- Name: tire_pkey; Type: CONSTRAINT; Schema: public; Owner: ot04-5
--

ALTER TABLE ONLY tire
    ADD CONSTRAINT tire_pkey PRIMARY KEY (id);


--
-- TOC entry 25 (OID 80432400)
-- Name: preferences_pkey; Type: CONSTRAINT; Schema: public; Owner: ot04-5
--

ALTER TABLE ONLY preferences
    ADD CONSTRAINT preferences_pkey PRIMARY KEY (id);


--
-- TOC entry 26 (OID 80432411)
-- Name: dateformat_pkey; Type: CONSTRAINT; Schema: public; Owner: ot04-5
--

ALTER TABLE ONLY dateformat
    ADD CONSTRAINT dateformat_pkey PRIMARY KEY (id);


SET SESSION AUTHORIZATION 'postgres';

--
-- TOC entry 3 (OID 2200)
-- Name: SCHEMA public; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON SCHEMA public IS 'Standard public namespace';


