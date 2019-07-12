--
-- PostgreSQL database dump
--

-- Dumped from database version 10.9
-- Dumped by pg_dump version 10.9

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- Name: postgis; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS postgis WITH SCHEMA public;


--
-- Name: EXTENSION postgis; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION postgis IS 'PostGIS geometry, geography, and raster spatial types and functions';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: avatar; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.avatar (
    avatar_id character varying NOT NULL,
    avatar_label character varying
);


ALTER TABLE public.avatar OWNER TO postgres;

--
-- Name: photo; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.photo (
    photo_id character varying NOT NULL,
    taken_time date,
    lat numeric,
    lon numeric,
    path character varying,
    photo_label character varying,
    avatar_id character varying
);


ALTER TABLE public.photo OWNER TO postgres;

--
-- Data for Name: avatar; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.avatar (avatar_id, avatar_label) FROM stdin;
\.


--
-- Data for Name: photo; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.photo (photo_id, taken_time, lat, lon, path, photo_label, avatar_id) FROM stdin;
\.


--
-- Data for Name: spatial_ref_sys; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.spatial_ref_sys (srid, auth_name, auth_srid, srtext, proj4text) FROM stdin;
\.


--
-- Name: avatar avatar_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.avatar
    ADD CONSTRAINT avatar_pkey PRIMARY KEY (avatar_id);


--
-- Name: photo photo_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.photo
    ADD CONSTRAINT photo_pkey PRIMARY KEY (photo_id);


--
-- Name: photo photo_avatar_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.photo
    ADD CONSTRAINT photo_avatar_id_fkey FOREIGN KEY (avatar_id) REFERENCES public.avatar(avatar_id);


--
-- PostgreSQL database dump complete
--

