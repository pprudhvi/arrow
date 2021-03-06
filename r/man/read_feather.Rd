% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/feather.R
\name{read_feather}
\alias{read_feather}
\title{Read a Feather file}
\usage{
read_feather(file, col_select = NULL, as_tibble = TRUE, ...)
}
\arguments{
\item{file}{an \code{arrow::ipc::feather::TableReader} or whatever the \code{\link[=FeatherTableReader]{FeatherTableReader()}} function can handle}

\item{col_select}{\link[tidyselect:vars_select]{tidy selection} of columns to read.}

\item{as_tibble}{should the \link[=arrow__Table]{arrow::Table} be converted to a tibble.}

\item{...}{additional parameters}
}
\value{
A \code{data.frame} if \code{as_tibble} is \code{TRUE} (the default), or a \link[=arrow__Table]{arrow::Table} otherwise
}
\description{
Read a Feather file
}
